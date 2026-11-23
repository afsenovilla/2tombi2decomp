#!/usr/bin/env python3
"""Dispatcher drafter: a ready scratch for a pending function that holds inlined copies of matched functions.

  python3 -I tools/dispatch.py --list [PROG ...] [--min 2] [--top 40]
  python3 -I tools/dispatch.py PROG NAME [NAME ...] [--min-cover 0.8] [--min-len 10] [--out DIR] [--no-check]

--list: the pending functions of the programs (default all) in which tools/inlined.py finds two or more matched
bodies at places that do not overlap (dispatchers: a switch / sequence of handlers), most covered first, with the
bodies, their cover and register consistency, and the differing constants of each copy.

PROG NAME: writes build/dispatch/<prog>/<name>.c, an install_c.py scratch:
  - every matched body found inside (best first, spans that do not overlap) as a `static inline` helper headed
    `/* NAME, inlined */` (the helper the target program already has for it when there is one, else the matched
    C renamed `inl_XXXXXXXX`), with the declarations it uses (types, externs, macros, other helpers, transitively);
    symbols of a body from another program are renamed to the target's names through the aligned instructions
    (`%hi(D_x)` / `jal f` operands), and a differing immediate whose literal occurs once in the helper is patched
    (the rest is listed in the header: `op:K->K2`);
  - the caller skeleton: m2c on the pending asm with each inlined span replaced by the helper call (the helper's
    parameters moved from the registers the copy uses; exits of the span kept as branches: `beqz $v0` on the
    helper's result for a conditional exit), so the draft reads `inl_X(arg0);` where the copy was;
  - a header comment: the spans, the register maps, what to check (a helper whose exits branch into the caller
    is a value-returning helper used in a condition; constants that still differ).
The scratch is then checked with tools/ccheck.py (words off printed) unless --no-check. It is a start: fix the
draft's types (m2c's `?`, `unkXX` fields), the helper calls' arguments and the case bodies, then ccheck / install.
"""
import argparse, collections, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import decomp, dupsweep as DS, inlined as I, nearcopy as N, ptsrc

OUT = os.path.join(ROOT, "build", "dispatch")
SYM = re.compile(r"%(?:hi|lo)\(([A-Za-z_]\w*)|^\s*(?:jal|j)\s+([A-Za-z_]\w*)\s*$")
BRANCH = re.compile(r"^(b|beq|bne|beqz|bnez|blez|bgtz|bltz|bgez|bltzal|bgezal|beql|bnel|j|jal|jr|jalr)$")
INS = re.compile(r"^(\s*/\* \w+ )([0-9A-F]{8})( [0-9A-F]{8} \*/\s+)(\S+)(\s*)(.*)$")


def parse_asm(path):
    """lines of a splat .s file, the instruction lines (index, address, mnemonic, operands) and label addresses."""
    lines = open(path).read().split("\n")
    ins, labels, pend_labels = [], {}, []
    for i, l in enumerate(lines):
        m = re.match(r"\s*(\.L\w+):\s*$", l) or re.match(r"\s*jlabel\s+(\.L\w+)\s*$", l)
        if m:
            pend_labels.append(m.group(1))
            continue
        m = INS.match(l)
        if m:
            ad = int(m.group(2), 16)
            for lb in pend_labels:
                labels[lb] = ad
            pend_labels = []
            ins.append((i, ad, m.group(4), m.group(6)))
    return lines, ins, labels


def is_branch(mn):
    return bool(BRANCH.match(mn))


def reg_map(hit):
    """body register -> pending register (the most frequent pairing over the aligned blocks)."""
    cnt = collections.defaultdict(collections.Counter)
    b, p = hit["_body"], hit["_pend"]
    for i, j, n in hit["_blocks"]:
        for k in range(n):
            for x, y in zip(b[i + k][1], p[j + k][1]):
                cnt[x][y] += 1
    return {x: c.most_common(1)[0][0] for x, c in cnt.items()}


def body_lines(prog, name):
    return I.read_funcs(prog).get(name) or []


def param_regs(lines, n):
    """for each of the n first parameters, the registers that hold it in the body: aN and the saved registers it
    is copied to (`move sX, aN`) before aN is written again."""
    out = [{4 + i} for i in range(n)]
    live = {4 + i: i for i in range(n)}
    stop = False
    for w, mn, ops, ad in lines[:40]:
        if stop:
            stop = None
        op, rs, rt, rd, fn = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, w & 0x3F
        if op == 0 and fn in (0x21, 0x25) and (rt == 0) != (rs == 0) and rd != 0:
            src = rs or rt
            if src in live:
                out[live[src]].add(rd)
                if stop is None:
                    break
                continue
        if stop is None:
            break                                          # the delay slot of the first call is done
        # the destination of any other instruction ends the parameter's life in it
        dst = rd if op == 0 else rt if op not in (1, 2, 3, 4, 5, 6, 7) and op < 0x28 else None
        if op == 3:
            stop = True                                    # a call: only its delay slot is left
        if dst in live:
            del live[dst]
    return out


def ret_reg(lines):
    """the register the body's result comes from: R of a final `move $v0, R` before its `jr $ra`, else v0."""
    for k in range(len(lines) - 1, -1, -1):
        if lines[k][1] == "jr" and lines[k][2].strip() == "$ra":
            for w, mn, ops, ad in reversed(lines[max(0, k - 8):k + 2]):
                op, rs, rt, rd, fn = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, w & 0x3F
                if op == 0 and fn in (0x21, 0x25) and rd == 2 and (rt == 0) != (rs == 0):
                    return rs or rt
                if (op == 0 and rd == 2) or (op not in (0, 1, 2, 3) and op < 0x28 and rt == 2):
                    return 2
            break
    return 2


def sym_pairs(hit, blines, plines):
    """{body symbol: pending symbol} read from the operands of the aligned instructions."""
    bad = {x[2]: x for x in blines}
    pad = {x[2]: x for x in plines}
    out = {}
    b, p = hit["_body"], hit["_pend"]
    for i, j, n in hit["_blocks"]:
        for k in range(n):
            x, y = bad.get(b[i + k][2]), pad.get(p[j + k][2])
            if not x or not y:
                continue
            sx = [g for m in SYM.finditer(x[1] + " " + x[2] if x[1] in ("jal", "j") else x[2]) for g in m.groups()
                  if g]
            sy = [g for m in SYM.finditer(y[1] + " " + y[2] if y[1] in ("jal", "j") else y[2]) for g in m.groups()
                  if g]
            for u, v in zip(sx, sy):
                if u != v and not u.startswith(".") and not v.startswith("."):
                    out.setdefault(u, v)
    return out


def helper_name(name):
    m = re.fullmatch(r"func_([0-9A-F]{8})", name)
    return "inl_" + m.group(1) if m else name + "_inl"


def target_helpers(prog):
    """(matched name -> (helper name, text)) of the `/* NAME, inlined */` helpers of src/<prog>/<prog>.c."""
    p = os.path.join(ROOT, "src", prog, prog + ".c")
    out = {}
    if not os.path.exists(p):
        return out
    t = open(p).read()
    for m in re.finditer(r"/\*[^*]*?(\w+), inlined \*/\s*\n", t):
        segs = ptsrc.items(t[m.end():])
        for kind, seg in segs:
            s = seg.strip()
            if kind == "code" and s.startswith("static") and s.endswith("}"):
                out.setdefault(m.group(1), (ptsrc.func_name(s), s))
            break
    return out


def make_helper(hit, tprog, have):
    """(helper name, helper text, its declarations, notes) for one hit."""
    bprog, bname = hit["_bk"]
    notes = []
    if bname in have:
        hname, text = have[bname]
        return hname, "/* %s, inlined */\n%s" % (bname, text), [], ["%s: the target's helper %s" % (bname, hname)]
    fs = DS.c_functions(bprog)
    if bname not in fs:
        return None, None, [], ["%s: no C text in src/%s (a library file?)" % (bname, bprog)]
    text, decls = fs[bname]
    hname = helper_name(bname)
    text = re.sub(r"^((?:static\s+|inline\s+)*)", "", text)
    text = "static inline " + re.sub(r"\b%s\b" % re.escape(bname), hname, text, count=1)
    need = DS.needed(text, decls)
    if bprog != tprog:
        ren = sym_pairs(hit, body_lines(bprog, bname), I.read_funcs(tprog)[hit["_pk"][1]])
        if ren:
            text = N.apply_renames(text, ren)
            need = [N.apply_renames(e, ren) for e in need]
            notes.append("%s: symbols renamed for %s: %s" % (bname, tprog, ", ".join(
                "%s -> %s" % kv for kv in sorted(ren.items()))))
    left = []
    for c in (hit["consts"].split() if hit["consts"] != "-" else []):
        op, kk = c.split(":")
        k1, k2 = (int(v, 16) for v in kk.split("->"))
        lits = [m for m in re.finditer(r"(?<![\w.])(0x[0-9A-Fa-f]+|\d+)\b", text) if int(m.group(1), 0) == k1]
        if len(lits) == 1:
            m = lits[0]
            text = text[:m.start()] + ("0x%X" % k2 if m.group(1).startswith("0x") else str(k2)) + text[m.end():]
            notes.append("%s: constant %s patched (%s)" % (bname, c, op))
        else:
            left.append(c)
    if left:
        notes.append("%s: constants that differ in the copy, not patched: %s" % (bname, " ".join(left)))
    return hname, "/* %s, inlined */\n%s" % (bname, text), need, notes


def nparams(text):
    """(parameter count, return type is void, parameter C types) of a helper's definition."""
    head = ptsrc.strip_comments(text[:text.find("{")])
    m = re.search(r"\(([^()]*)\)\s*$", head.strip())
    args = m.group(1).strip() if m else ""
    ps = [] if args in ("", "void") else [x.strip() for x in args.split(",")]
    ret = head[:head.rfind("(")]
    ret = re.sub(r"\b(static|inline)\b", "", ret).strip().rsplit(None, 1)[0] if ret.strip() else "void"
    return len(ps), ret.strip() == "void", ps


def proto_for(hname, text):
    n, void, ps = nparams(text)
    ts = ["void *" if "*" in p else "s32" for p in ps]
    return "%s %s(%s);" % ("void" if void else "s32", hname, ", ".join(ts) or "void")


def rewrite_asm(path, spans):
    """the pending asm with each span (start, end, helper, moves) replaced by the call; -> (text, notes)."""
    lines, ins, labels = parse_asm(path)
    byad = {ad: k for k, (_, ad, _, _) in enumerate(ins)}
    notes = []
    jt = set(re.findall(r"\.L\w+", "\n".join(l for l in lines if re.match(r"\s*jlabel\s", l))))
    for s, e, hname, moves, void, res in spans:
        ks, ke = byad.get(s), byad.get(e)
        if ks is None or ke is None:
            continue
        if ks > 0 and is_branch(ins[ks - 1][2]):
            ks += 1                                        # the first copied insn sits in a delay slot
        if is_branch(ins[ke][2]) and ke + 1 < len(ins):
            ke += 1                                        # the span ends with a branch: take its delay slot
        if ke + 1 < len(ins) and is_branch(ins[ke + 1][2]) and ins[ke + 1][2] in ("j", "b") and \
                ke + 2 < len(ins):
            ke += 2                                        # the case's `j` out after the copy
        endad = ins[ke][1]
        exits_c, exits_u = [], []
        for k in range(ks, ke + 1):
            mn, ops = ins[k][2], ins[k][3]
            if not is_branch(mn) or mn in ("jal", "jalr", "jr"):
                continue
            tgt = ops.split(",")[-1].strip()
            ta = labels.get(tgt)
            if ta is None or s <= ta <= endad or ta == endad + 4:
                continue
            (exits_u if mn in ("j", "b") else exits_c).append(tgt)
        # the helper's own returns: a branch to where the copy ends (its final `j` or the fall-through) or to
        # the epilogue (the caller returns right after the copy) is not a result test
        end_t = exits_u[-1] if exits_u and ins[ke - 1][2] in ("j", "b") else None
        same = {end_t} | {t for t in exits_c + exits_u if is_epilogue(ins, byad, labels.get(t))}
        if end_t is None and any(t in same for t in exits_c):
            end_t = next(t for t in exits_c if t in same)       # every path leaves to the epilogue
        exits_c = [x for x in dict.fromkeys(exits_c) if x not in same]
        exits_u = [end_t] if end_t else [x for x in dict.fromkeys(exits_u) if x not in exits_c]
        new = ["addu $%s, $%s, $zero" % (I_REG[d], I_REG[r]) for d, r in moves]
        new += ["jal %s" % hname, "nop"]
        if res is not None and res != 2:
            new += ["addu $%s, $v0, $zero" % I_REG[res]]       # the result where the copy leaves it
        for t in exits_c:
            new += ["beqz $v0, %s" % t, "nop"]
        for t in exits_u[:1]:
            new += ["j %s" % t, "nop"]
        if exits_c:
            notes.append("%s: the copy at %08X branches out to %s: a value-returning helper used in a condition "
                         "(beqz on its result stands in for each exit; check which result goes where)"
                         % (hname, s, " ".join(exits_c)))
        # labels inside the copy reached from outside it: a cross-jumped tail shared with other code, or
        # another case entering the copy: that code is not in the draft
        inside = {lb for lb, ad in labels.items() if ins[ks][1] < ad <= endad}
        refs = set()
        for k, (_, ad, mn, ops) in enumerate(ins):
            if (k < ks or k > ke) and is_branch(mn):
                refs.add(ops.split(",")[-1].strip())
        shared = sorted((inside & refs) | (inside & jt))
        if shared:
            notes.append("%s: code inside the copy is also reached from outside (%s: a tail gcc cross-jumped, or "
                         "a case entering it): that path is missing from the draft; write it out in full (gcc "
                         "merges the identical tails again), from tools/decomp.py's draft" % (hname, ", ".join(
                             "%s %08X" % (lb, labels[lb]) for lb in shared)))
        if len(new) > ke - ks + 1:
            notes.append("%s: span %08X-%08X too short for the call, left as is" % (hname, s, endad))
            continue
        new += ["nop"] * (ke - ks + 1 - len(new))
        for k, txt in zip(range(ks, ke + 1), new):
            li, ad, mn, ops = ins[k]
            m = INS.match(lines[li])
            mn2, _, ops2 = txt.partition(" ")
            lines[li] = "%s%08X 00000000 */  %-10s %s" % (m.group(1), ad, mn2, ops2.strip())
        notes.append("%s: replaces %08X-%08X" % (hname, ins[ks][1], endad))
    return "\n".join(lines), notes


def is_epilogue(ins, byad, ad):
    """the instructions at `ad` restore registers and return (`lw $ra / $sN, K($sp)` ... `jr $ra`)."""
    k = byad.get(ad)
    if k is None:
        return False
    for _, _, mn, ops in ins[k:k + 14]:
        if mn == "jr" and ops.strip() == "$ra":
            return True
        if not (mn == "lw" and ops.endswith("($sp)")) and mn != "nop" and not (mn == "addiu" and "$sp" in ops):
            return False
    return False


I_REG = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
         "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"]


def candidates(progs, min_cover=0.8, min_len=10):
    hits = I.search(progs, N.progs_list(), min_len, min_cover)
    byf = collections.defaultdict(list)
    for h in hits:
        byf[(h["prog"], h["name"])].append(h)
    out = []
    for k, hs in byf.items():
        sp = I.spans(hs)
        if len(sp) >= 2:
            cov = sum(int(h["end"], 16) - int(h["start"], 16) + 4 for h in sp) / hs[0]["size"]
            out.append((cov, k, sp, hs[0]["size"]))
    out.sort(key=lambda x: -x[0])
    return out


def draft(prog, name, hits, out_dir, check=True):
    sp = I.spans(hits)
    have = target_helpers(prog)
    path = decomp.find_asm(prog, name)
    helpers, decls, notes, spans, protos, regs_notes = [], [], [], [], [], []
    for h in sp:
        hname, text, need, nt = make_helper(h, prog, have)
        notes += nt
        if not hname:
            continue
        if hname in [x[0] for x in helpers]:
            continue
        helpers.append((hname, text))
        for e in need:
            if e not in decls:
                decls.append(e)
        n, void, _ = nparams(text)
        rm = reg_map(h)
        moves = []
        for i, regs in enumerate(param_regs(body_lines(*h["_bk"]), n)):
            # the saved register the body keeps the parameter in says more than aN (reloaded before each call)
            got = [rm[r] for r in sorted(regs, key=lambda r: (r < 16, r)) if r in rm]
            if got and got[0] != 4 + i:
                moves.append((4 + i, got[0]))
        regs_notes.append("%s (%s, cover %.2f, regs %.2f): %s" % (hname, h["from"], h["cover"], h["regs"], ", ".join(
            "%s->%s" % (I_REG[x], I_REG[y]) for x, y in sorted(rm.items()) if x != y and x not in (0, 29))
            or "same registers"))
        bl = body_lines(*h["_bk"])
        res = None if void else rm.get(ret_reg(bl))
        spans.append((int(h["start"], 16), int(h["end"], 16), hname, moves, void, res))
        protos.append(proto_for(hname, ptsrc.strip_comments(text).strip()))
    asm, nt = rewrite_asm(path, spans)
    notes += nt
    os.makedirs(os.path.join(ROOT, "build", "dispatch_tmp"), exist_ok=True)
    tmp_s = os.path.join(ROOT, "build", "dispatch_tmp", name + ".s")
    open(tmp_s, "w").write(asm)
    ctx = decomp.context()
    ctx2 = os.path.join(ROOT, "build", "dispatch_tmp", "ctx_%s.c" % name)
    open(ctx2, "w").write(open(ctx).read() + "\n" + "\n".join(protos) + "\n")
    jt = decomp.jtbl_file(prog)
    r = subprocess.run([sys.executable, decomp.M2C, "--target", "mipsel-gcc-c", "--valid-syntax", "--no-cache", "--context", ctx2,
                        tmp_s] + ([jt] if jt else []), capture_output=True, text=True, cwd=ROOT)
    body = r.stdout
    if r.returncode or not body.strip():
        body = "/* m2c failed: %s */\n" % (r.stderr.strip().splitlines() or ["?"])[-1]
    body = re.sub(r"(?m)^(extern )?\? ", r"\1s32 ", body)
    body = re.sub(r"(?m)^(.*/\* extern \*/)$", lambda m: re.sub(r"\?", "s32", m.group(1)), body)
    # target program declarations of the names the draft uses; drop m2c's externs for declared names
    tdecls = []
    tf = DS.c_functions(prog)
    if tf:
        tdecls = next(iter(tf.values()))[1]
    for e in DS.needed(body, [d for d in tdecls if not d.startswith("static")]):
        if e not in decls:
            decls.append(e)
    declared = set()
    for e in decls:
        declared |= DS.decl_names(e) or set()
    declared |= {h for h, _ in helpers}
    keep = []
    for l in body.split("\n"):
        m = re.match(r"(?:extern\s+)?[\w\s\*]+?\b(\w+)\s*(?:\(|\[|;)", l)
        if m and not l.startswith((" ", "\t", "}")) and l.rstrip().endswith(";") and m.group(1) in declared:
            continue
        keep.append(l)
    body = "\n".join(keep)
    tp = N.Prog(prog)
    head = ["/* tools/dispatch.py draft of %s (%s, %#x bytes): %d inlined bodies" % (name, prog, hits[0]["size"],
                                                                                  len(helpers)),
            " * register maps (body -> here): " + "\n *   ".join([""] + regs_notes)]
    if notes:
        head.append(" * notes:" + "\n *   ".join([""] + notes))
    head.append(" * next: fix the draft's types and the helper calls' arguments, then\n"
                " *   python3 -I tools/ccheck.py THIS.c --prog %s --func %s --sbs\n"
                " *   python3 -I tools/install_c.py THIS.c --prog %s */" % (prog, name, prog))
    # a helper that is also a declaration another helper needs (a static inline the body program defines) is
    # written once, where the declarations are (it comes before its users there)
    indecls = set()
    for e in decls:
        if e.startswith("static"):
            indecls |= DS.decl_names(e) or set()
    helpers = [(h, t) for h, t in helpers if h not in indecls]
    seen_def, dd = set(), []
    for e in decls:
        n = ptsrc.func_name(e) if e.startswith("static") else None
        if n and n in seen_def:
            continue
        if n:
            seen_def.add(n)
        dd.append(e)
    decls = dd
    src = N.PRELUDE + "".join(i + "\n" for i in tp.includes) + "\n".join(head) + "\n\n" + \
        "\n".join(decls) + "\n\n" + "\n\n".join(t for _, t in helpers) + "\n\n" + body.strip() + "\n"
    os.makedirs(os.path.join(out_dir, prog), exist_ok=True)
    out = os.path.join(out_dir, prog, name + ".c")
    open(out, "w").write(src)
    for f in (tmp_s, ctx2):
        os.remove(f)
    res = ""
    if check:
        r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "ccheck.py"), out, "--prog", prog,
                            "--func", name], capture_output=True, text=True, cwd=ROOT)
        res = (r.stdout.strip().splitlines() or [r.stderr.strip().splitlines()[-1] if r.stderr.strip() else "?"])[-1]
    return out, res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("args", nargs="*", help="PROG NAME [NAME ...], or with --list the programs")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--min-cover", type=float, default=0.8)
    ap.add_argument("--min-len", type=int, default=10)
    ap.add_argument("--min", type=int, default=2, help="--list: at least this many bodies")
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--no-check", action="store_true")
    a = ap.parse_args()
    if a.list:
        progs = a.args or N.progs_list()
        c = [x for x in candidates(progs, a.min_cover, a.min_len) if len(x[2]) >= a.min]
        print("%d pending functions hold %d+ matched bodies at different places (covered part first):" % (len(c), a.min))
        for cov, (prog, name), sp, size in c[:a.top]:
            print("%-4s %-44s %#6x %3.0f%%  %s" % (prog, name, size, 100 * cov, "; ".join(
                "%s %.2f r%.2f%s" % (h["from"], h["cover"], h["regs"],
                                     " {%s}" % h["consts"] if h["consts"] != "-" else "") for h in sp)))
        return
    if len(a.args) < 2:
        ap.error("PROG NAME [NAME ...] or --list")
    prog, names = a.args[0], a.args[1:]
    hits = I.search([prog], N.progs_list(), a.min_len, a.min_cover, pending_only={(prog, n) for n in names})
    for name in names:
        hs = [h for h in hits if h["name"] == name]
        if not hs:
            print("%s: no inlined matched body found" % name)
            continue
        try:
            out, res = draft(prog, name, hs, a.out, not a.no_check)
        except Exception as e:    # m2c / parsing crash on one function: report it, go on with the others
            print("%s: draft failed: %s: %s" % (name, type(e).__name__, e))
            continue
        print("%s: %s%s" % (name, os.path.relpath(out, ROOT), ("  [" + res + "]") if res else ""))


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Actor state-machine drafter: a pending `switch (a[4])` function (sub-switches on a[3] / a[5]) as a scratch.

  python3 -I tools/statemachine.py --list [PROG ...] [--top 40]
  python3 -I tools/statemachine.py PROG NAME [NAME ...] [--out build/statemachine] [--no-check] [--actor [--actor-args 0,1]]

--list: the pending functions of the programs (default a00-a08) that dispatch through rodata jump tables, with the
number of tables / cases, the share of their calls that go to matched functions (C in src/) and the switch
operands (`a[4]`: an lbu of offset 4 feeding the table's sltiu), most promising first (all calls matched, small).

PROG NAME: writes build/statemachine/<prog>/<name>.c, an install_c.py scratch:
  - a header with every jump table: the byte it switches on (`lbu 4(s0)` -> a[4]), and for each case its target
    and what that case's block does (the jal targets, matched or not, and the matched bodies tools/inlined.py finds
    inlined there), so each case can be written as the call of its handler;
  - the matched bodies found inlined as `static inline` helpers (tools/dispatch.py: one definition each, the
    declarations they need, symbols renamed for the program, differing constants patched);
  - the function: two drafts are made, tools/dispatch.py's (each inlined span replaced by the helper call) and
    tools/decomp.py's plain m2c draft (every case in full, usually the better start for state machines); both are
    checked with tools/ccheck.py and the closer one is written as the function, the other to <name>.alt.c.
Then fix types / arguments (`--sbs`), write the cases with the helpers (each case in full: gcc cross-jumps the
shared tails itself), delete the draft header and install with tools/install_c.py. a06 func_80137148 went from the
decomp.py draft (50 words off) to a match at the first rewrite this way.
"""
import argparse, collections, glob, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import decomp, dispatch as DP, inlined as I, nearcopy as N

OUT = os.path.join(ROOT, "build", "statemachine")


def matched_names(prog):
    """names with C in the program and in MAIN.EXE (defined in src/<prog> / src/main, not INCLUDE_ASM): the
    overlays call MAIN's functions."""
    out = set()
    for f in glob.glob(os.path.join(ROOT, "src", prog, "**", "*.c"), recursive=True) + \
            (glob.glob(os.path.join(ROOT, "src", "main", "**", "*.c"), recursive=True) if prog != "main" else []):
        t = open(f, errors="replace").read()
        out |= set(re.findall(r"(?m)^[A-Za-z_][\w \*]*?\b(\w+)\s*\([^;{]*\)\s*\{", t))
    # an overlay's asm calls MAIN's functions by address (func_8007778C = f_TestAndQueueActorForRender)
    p = os.path.join(ROOT, "config", "symbol_addrs_main.txt")
    if prog != "main" and os.path.exists(p):
        for m in re.finditer(r"(?m)^(\w+)\s*=\s*0x([0-9A-Fa-f]{8})\s*;", open(p).read()):
            if m.group(1) in out:
                out.add("func_%s" % m.group(2).upper())
    return out


def jtbl_targets(prog):
    """jtbl label -> list of target labels (from asm/<prog>/data/*rodata*.s)."""
    out, cur = {}, None
    for s in sorted(glob.glob(os.path.join(ROOT, "asm", prog, "data", "*rodata*.s"))):
        for l in open(s):
            m = re.match(r"\s*(end)?dlabel (\w+)", l)
            if m:
                cur = m.group(2) if m.group(2).startswith("jtbl_") and not m.group(1) else None
                if cur:
                    out[cur] = []
                continue
            if cur:
                m = re.search(r"\.word\s+(\.?L\w+)", l)
                if m:
                    out[cur].append(m.group(1))
    return out


def analyse(prog, name, jt=None, matched=None):
    """(tables, calls) of a pending function: tables = [(jtbl, operand, [(case, label, address)])], calls = the jal
    targets in order of address [(address, target)]."""
    path = decomp.find_asm(prog, name)
    lines, ins, labels = DP.parse_asm(path)
    jt = jtbl_targets(prog) if jt is None else jt
    tables = []
    for k, (i, ad, mn, ops) in enumerate(ins):
        m = re.search(r"%hi\((jtbl_\w+)\)", ops)
        if not (m and m.group(1) in jt):
            continue
        # the switch operand: the nearest lbu / lhu / lw before the sltiu that bounds the index
        opnd = "?"
        for j in range(k - 1, max(-1, k - 12), -1):
            mm = re.match(r"(lbu|lb|lhu|lh|lw)$", ins[j][2])
            if mm:
                o = re.match(r"\$\w+,\s*(-?\w+)\((\$\w+)\)", ins[j][3])
                if o:
                    opnd = "%s %s(%s)" % (ins[j][2], o.group(1), o.group(2))
                    if mm.group(1) in ("lbu", "lb") and o.group(2) not in ("$sp", "$at"):
                        opnd += " = a[%d]" % int(o.group(1), 0)
                break
        cases = [(c, lb, labels.get(lb)) for c, lb in enumerate(jt[m.group(1)])]
        tables.append((m.group(1), opnd, cases))
    calls = [(ad, ops.strip()) for _, ad, mn, ops in ins if mn == "jal"]
    return tables, calls, ins


def case_blocks(tables, ins):
    """case target address -> end address (the next case target of any table after it, or the function end)."""
    starts = sorted({c[2] for _, _, cs in tables for c in cs if c[2] is not None})
    end = ins[-1][1] + 4 if ins else 0
    return {s: (starts[i + 1] if i + 1 < len(starts) else end) for i, s in enumerate(starts)}


def describe(prog, name, tables, calls, ins, hits, matched):
    blocks = case_blocks(tables, ins)
    out = []
    for jt, opnd, cases in tables:
        out.append("%s: switch on %s, %d cases" % (jt, opnd, len(cases)))
        by_target = collections.defaultdict(list)
        for c, lb, ad in cases:
            by_target[ad].append(c)
        for ad, cs in sorted(by_target.items(), key=lambda kv: (kv[0] is None, kv[0] or 0)):
            if ad is None:
                out.append("  case %s: ?" % ",".join(map(str, cs)))
                continue
            e = blocks.get(ad, ad)
            what = ["%s%s" % (t, "" if t in matched else " (asm)") for a2, t in calls if ad <= a2 < e]
            what += ["inlined %s" % h["from"] for h in hits if ad <= int(h["start"], 16) < e]
            out.append("  case %s -> %08X: %s" % (",".join(map(str, cs)), ad, "; ".join(what) or "-"))
    return out


def m2c_body(prog, name, actor=None):
    """m2c's draft (--valid-syntax); actor: the parameters typed Actor * ("0": arg0; tools/decomp.py --actor)."""
    ctx = decomp.actor_context(prog, name, actor) if actor else decomp.context()
    r = subprocess.run(decomp.m2c_cmd(prog, name, ctx, ("--valid-syntax",)), capture_output=True,
                       text=True, cwd=ROOT)
    if r.returncode or not r.stdout.strip():
        return None
    body = re.sub(r"(?m)^/\* extern \*/\n", "", r.stdout)
    body = re.sub(r"(?m)^(extern )?\? ", r"\1s32 ", body)
    return re.sub(r"(?m)^(.*/\* extern \*/)$", lambda m: re.sub(r"\?", "s32", m.group(1)), body)


def split_func(src, name):
    """(text before the function definition, the definition) of a scratch."""
    m = re.search(r"(?m)^[A-Za-z_][\w \*]*?\b%s\s*\(" % re.escape(name), src)
    return (src[:m.start()], src[m.start():]) if m else (src, "")


def check(path, prog, name):
    r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "ccheck.py"), path, "--prog", prog,
                        "--func", name], capture_output=True, text=True, cwd=ROOT)
    last = (r.stdout.strip().splitlines() or [r.stderr.strip().splitlines()[-1] if r.stderr.strip() else "?"])[-1]
    if last.startswith("OK"):
        return 0, last
    m = re.search(r"(\d+) words differ", last)
    return (int(m.group(1)) if m else 10 ** 6), last


def draft(prog, name, out_dir, do_check=True, jt=None, matched=None, actor=None):
    matched = matched_names(prog) if matched is None else matched
    tables, calls, ins = analyse(prog, name, jt, matched)
    hits = I.search([prog], N.progs_list(), 10, 0.8, pending_only={(prog, name)})
    hits = [h for h in hits if h["name"] == name]
    os.makedirs(os.path.join(out_dir, prog), exist_ok=True)
    out = os.path.join(out_dir, prog, name + ".c")
    alt = os.path.join(out_dir, prog, name + ".alt.c")
    head = ["/* tools/statemachine.py draft of %s (%s): %d jump tables, %d calls (%d to matched functions)," %
            (name, prog, len(tables), len(calls), sum(1 for _, t in calls if t in matched)),
            " * %d matched bodies inlined" % len(I.spans(hits)) if hits else " * no matched body inlined"]
    head += [" * " + l for l in describe(prog, name, tables, calls, ins, I.spans(hits) if hits else [], matched)]
    drafts = []
    if hits:
        try:
            p, _ = DP.draft(prog, name, hits, out_dir, check=False)
            drafts.append(("dispatch.py", open(p).read()))
        except Exception as e:     # m2c crash on the rewritten asm
            head.append(" * dispatch.py draft failed: %s: %s" % (type(e).__name__, e))
    body = m2c_body(prog, name, actor)
    if body and "Actor" in body:
        body = '#include "actor.h"\n' + body
    if body:
        if drafts:
            pre, _ = split_func(drafts[0][1], name)
            have = set(re.findall(r"\b\w+\b", pre))
            keep = []
            for l in body.split("\n"):    # m2c's top-level declarations of names the scratch already declares
                m = re.match(r"(?:extern\s+)?[\w\s\*]+?\b(\w+)\s*(?:\(|\[|;)", l)
                if m and not l.startswith((" ", "\t", "}")) and l.rstrip().endswith(";") and m.group(1) in have:
                    continue
                keep.append(l)
            drafts.append(("decomp.py", pre + "\n".join(keep).strip() + "\n"))
        else:
            tp = N.Prog(prog)
            drafts.append(("decomp.py", N.PRELUDE + "".join(i + "\n" for i in tp.includes) + "\n" + body.strip() + "\n"))
    if not drafts:
        head.append(" * m2c failed on this function")
        open(out, "w").write("\n".join(head) + " */\n")
        return out, "no draft"
    scored = []
    for kind, text in drafts:
        open(out, "w").write(text)
        sc = check(out, prog, name) if do_check else (0, "not checked")
        scored.append((sc[0], kind, text, sc[1]))
    scored.sort(key=lambda x: x[0])
    head.append(" * drafts: " + "; ".join("%s: %s" % (k, r) for _, k, _, r in scored))
    head.append(" * next: python3 -I tools/ccheck.py THIS.c --prog %s --func %s --sbs; tools/install_c.py THIS.c "
                "--prog %s */" % (prog, name, prog))
    hdr = "\n".join(head) + "\n"

    def put(path, text):
        # the header goes after the includes of the scratch
        m = re.search(r"\A((?:#include[^\n]*\n|\s*\n)*)", text)
        open(path, "w").write(text[:m.end()] + hdr + text[m.end():])
    put(out, scored[0][2])
    if len(scored) > 1:
        put(alt, scored[1][2])
    elif os.path.exists(alt):
        os.remove(alt)
    return out, "%s: %s" % (scored[0][1], scored[0][3])


def listing(progs, top):
    rows = []
    for prog in progs:
        jt = jtbl_targets(prog)
        matched = matched_names(prog)
        for name in sorted(I.pending_names(prog)[0]):
            try:
                tables, calls, ins = analyse(prog, name, jt, matched)
            except SystemExit:
                continue
            if not tables:
                continue
            ncase = sum(len(c) for _, _, c in tables)
            nm = sum(1 for _, t in calls if t in matched)
            share = nm / len(calls) if calls else 1.0
            ops = ",".join(sorted({o.split("= ")[-1] for _, o, _ in tables}))
            rows.append((-share, len(ins), prog, name, len(tables), ncase, nm, len(calls), ops))
    rows.sort()
    print("%d pending functions with jump tables (matched calls first, then smaller):" % len(rows))
    for s, n, prog, name, nt, nc, nm, ncall, ops in rows[:top]:
        print("%-4s %-46s %#6x  %d tables %3d cases  calls %d/%d matched  %s" % (prog, name, 4 * n, nt, nc, nm,
                                                                                ncall, ops))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("args", nargs="*")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--no-check", action="store_true")
    ap.add_argument("--actor", action="store_true", help="m2c draft with arg0 typed Actor * (include/actor.h)")
    ap.add_argument("--actor-args", default="0", help="with --actor: the parameters typed Actor * (e.g. 0,1)")
    a = ap.parse_args()
    if a.list:
        listing(a.args or ["a0%d" % i for i in range(9)], a.top)
        return
    if len(a.args) < 2:
        ap.error("PROG NAME [NAME ...] or --list [PROG ...]")
    prog = a.args[0]
    jt, matched = jtbl_targets(prog), matched_names(prog)
    for name in a.args[1:]:
        try:
            out, res = draft(prog, name, a.out, not a.no_check, jt, matched, a.actor_args if a.actor else None)
        except Exception as e:
            print("%s: failed: %s: %s" % (name, type(e).__name__, e))
            continue
        print("%s: %s  [%s]" % (name, os.path.relpath(out, ROOT), res))


if __name__ == "__main__":
    main()

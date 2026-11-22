"""`// RETURN sony` (tools/cc.py): rewrite gcc 2.8.1's cc1 output to the one-return code Sony's library compiler gave.

gcc 2.8.1 emits a `j $31` for every return path of a frameless function (its `return` insn); the retail library
branches to one final `jr ra; nop` instead, as a gcc without that insn does:
  1. every `j $31` but the last one of the function becomes `j $LSRn`; the last one becomes `$LSRn: jr ra; nop`
     (its delay-slot insn, if any, goes before the label);
  2. a `j $LSRn` that would fall into `$LSRn` (only labels between) is dropped, its delay-slot insn kept inline;
  3. jump threading: `bCOND a,b,L` (reorder mode) over a `j $LSRn; D` block that ends at `L:` becomes
     `bINVCOND a,b,$LSRn; D` when D's destination is dead on the fall-through path; a label on the `j` block (other
     branches use it) moves the block after the next unconditional jump. A branch whose delay slot holds the first
     insn of its target (gcc's reorg) gets that insn back inline after the new branch.
Units: labels, plain insns (reorder mode), `.set noreorder` groups (branch + delay slot), other lines.
"""
import re

INV = {"beq": "bne", "bne": "beq", "blez": "bgtz", "bgtz": "blez", "bltz": "bgez", "bgez": "bltz"}
STORES = {"sb", "sh", "sw", "swl", "swr", "swc2", "sdc2"}
LOADS = {"lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr"}
LAB = re.compile(r"^(\$?[\w.]+):$")


def parse(body):
    out, lines, i = [], body.split("\n"), 0
    while i < len(lines):
        l = lines[i]
        if l == "\t.set\tnoreorder":
            ins, raw = [], [l]
            i += 1
            while i < len(lines) and lines[i] != "\t.set\treorder":
                raw.append(lines[i])
                if lines[i].startswith("\t") and not lines[i].startswith("\t.") and not lines[i].startswith("\t#"):
                    ins.append(lines[i].strip())
                i += 1
            raw.append("\t.set\treorder")
            op = ins[0].split()[0] if ins else ""
            if len(ins) == 2 and (op in INV or op == "j"):
                out.append({"k": "grp", "ins": ins})
            else:
                out.append({"k": "raw", "t": "\n".join(raw)})
        elif LAB.match(l):
            out.append({"k": "lab", "name": LAB.match(l).group(1)})
        elif l.startswith("\t") and not l.startswith("\t.") and not l.startswith("\t#") and l.strip():
            out.append({"k": "ins", "t": l.strip()})
        else:
            out.append({"k": "raw", "t": l})
        i += 1
    return out


def emit(units):
    o = []
    for u in units:
        if u["k"] == "grp":
            o.append("\t.set\tnoreorder\n\t.set\tnomacro\n\t%s\n\t%s\n\t.set\tmacro\n\t.set\treorder" % tuple(u["ins"]))
        elif u["k"] == "lab":
            o.append(u["name"] + ":")
        elif u["k"] == "ins":
            o.append("\t" + u["t"])
        else:
            o.append(u["t"])
    return "\n".join(o)


def first(u):
    return u["ins"][0] if u["k"] == "grp" else u["t"] if u["k"] == "ins" else None


def jump_to(u, lab):
    """(True, delay insn or None) when unit u is `j lab`."""
    f = first(u)
    if f == "j\t" + lab:
        return True, u["ins"][1] if u["k"] == "grp" else None
    return False, None


def regs(insn):
    """(op, written register or None, read registers) of a cc1 insn."""
    p = insn.split(None, 1)
    op, args = p[0], (p[1].split("#")[0] if len(p) > 1 else "")
    ops = [a.strip() for a in args.split(",") if a.strip()]
    found = lambda a: re.findall(r"\$\w+", a)
    if op in STORES or op in INV or op[0] in "bj":
        return op, None, [r for a in ops for r in found(a)]
    if not ops:
        return op, None, []
    return op, ops[0], [r for a in ops[1:] for r in found(a)]


def dead_after(units, i, reg):
    """Is reg dead on the straight-line path that starts after unit i? (conservative: unknown is live)"""
    if reg in ("$0", None):
        return True
    for u in units[i + 1:]:
        if u["k"] in ("lab", "raw"):
            if u["k"] == "raw" and u["t"].strip() and not u["t"].strip().startswith("."):
                return False
            continue
        for n, insn in enumerate(u["ins"] if u["k"] == "grp" else [u["t"]]):
            op, w, r = regs(insn)
            if reg in r:
                return False
            if w == reg:
                return True
            if n == 0 and (op in INV or op[0] in "bj") and u["k"] == "ins":
                return False     # a reorder-mode branch: its delay slot is the assembler's
        if u["k"] == "grp":
            return False
    return False


def next_unit(units, i, kinds=("ins", "grp")):
    j = i + 1
    while j < len(units) and units[j]["k"] not in kinds:
        j += 1
    return j


def refs(units, name):
    return sum(1 for u in units if u["k"] in ("ins", "grp") and re.search(r"[,\t]%s$" % re.escape(name), first(u)))


def early_first(units, lab):
    """`RETURN sony first`: the short return block that gcc moved to the end (`L: [Y]` just before the return
    label, reached by one branch) goes back right after that branch, as written in C:
        bCOND a,b,L; X / BODY / j LSR; D / L: Y / LSR:   ->   bINV a,b,Lb; X / j LSR; Y / Lb: BODY / D / LSR:
    D (the body's return value, in the old jump's delay slot) goes back after the body's last load, where gcc's
    scheduler had it."""
    r = next(i for i, u in enumerate(units) if u["k"] == "lab" and u["name"] == lab)
    # L: [Y] directly before the return label
    j = r - 1
    while j >= 0 and units[j]["k"] == "raw":
        j -= 1
    y = None
    if units[j]["k"] == "ins":
        y, j = units[j]["t"], j - 1
        while j >= 0 and units[j]["k"] == "raw":
            j -= 1
    if units[j]["k"] != "lab":
        return units
    L, li = units[j]["name"], j
    if refs(units, L) != 1:
        return units
    b = next((i for i, u in enumerate(units[:li]) if u["k"] in ("ins", "grp") and
              re.match(r"(\w+)\t(.*),%s$" % re.escape(L), first(u))), None)
    if b is None:
        return units
    m = re.match(r"(\w+)\t(.*),(\$\w+)$", first(units[b]))
    if m.group(1) not in INV:
        return units
    k = li - 1
    while units[k]["k"] == "raw":
        k -= 1
    is_j, d = jump_to(units[k], lab)
    if not is_j:
        return units
    x = units[b]["ins"][1] if units[b]["k"] == "grp" else None
    if y is not None and x == y:
        return units
    lb = "%s_B" % lab
    head = [{"k": "grp", "ins": ["%s\t%s,%s" % (INV[m.group(1)], m.group(2), lb), x]} if x else
            {"k": "ins", "t": "%s\t%s,%s" % (INV[m.group(1)], m.group(2), lb)},
            {"k": "grp", "ins": ["j\t" + lab, y or "nop"]}, {"k": "lab", "name": lb}]
    body = units[b + 1:k]
    if d and d != "nop":
        body = place_in_load_delay(body, d)
    return units[:b] + head + body + units[r:]


def place_in_load_delay(body, d):
    """d goes right after the last load of the last straight-line run of body (gcc's scheduler fills the load
    delay with the independent return-value insn), else at the end; only if d does not conflict with the insns it
    moves over."""
    start = len(body)
    while start > 0 and body[start - 1]["k"] in ("ins", "raw"):
        start -= 1
    _, dw, dr = regs(d)
    ins = [i for i in range(start, len(body)) if body[i]["k"] == "ins"]
    loads = [n for n, i in enumerate(ins) if regs(body[i]["t"])[0] in LOADS]
    if loads:
        n = loads[-1]
        later = [regs(body[x]["t"]) for x in ins[n + 1:]]
        if all(dw not in r and dw != w2 and w2 not in dr for _, w2, r in later):
            i = ins[n]
            return body[:i + 1] + [{"k": "ins", "t": d}] + body[i + 1:]
    return body + [{"k": "ins", "t": d}]


def rewrite_function(body, n, first_mode=False):
    units = parse(body)
    rets = [i for i, u in enumerate(units) if first(u) == "j\t$31"]
    if len(rets) < 2:
        return body
    lab = "$LSR%d" % n
    for i in rets[:-1]:
        units[i] = dict(units[i])
        if units[i]["k"] == "grp":
            units[i]["ins"] = ["j\t" + lab, units[i]["ins"][1]]
        else:
            units[i]["t"] = "j\t" + lab
    last = units[rets[-1]]
    tail = [{"k": "lab", "name": lab}, {"k": "grp", "ins": ["j\t$31", "nop"]}]
    if last["k"] == "grp" and last["ins"][1] != "nop":
        tail.insert(0, {"k": "ins", "t": last["ins"][1]})
    units[rets[-1]:rets[-1] + 1] = tail
    changed = True
    while changed:
        changed = False
        # 2. a jump that falls into the return label
        for i, u in enumerate(units):
            is_j, d = jump_to(u, lab)
            if not is_j:
                continue
            j = next_unit(units, i, ("ins", "grp", "lab"))
            while j < len(units) and units[j]["k"] == "lab" and units[j]["name"] != lab:
                j = next_unit(units, j, ("ins", "grp", "lab"))
            if j < len(units) and units[j]["k"] == "lab":
                units[i:i + 1] = [{"k": "ins", "t": d}] if d and d != "nop" else []
                changed = True
                break
        if changed:
            continue
        # 3. branch over a return
        for i, u in enumerate(units):
            if u["k"] not in ("ins", "grp"):
                continue
            m = re.match(r"(\w+)\t(.*),(\$\w+)$", first(u))
            if not m or m.group(1) not in INV:
                continue
            x = u["ins"][1] if u["k"] == "grp" else None   # delay insn taken from the target: kept inline
            if x == "nop":
                x = None
            target = m.group(3)
            j = next_unit(units, i, ("ins", "grp", "lab"))
            labels = []
            while j < len(units) and units[j]["k"] == "lab":
                labels.append(j)
                j = next_unit(units, j, ("ins", "grp", "lab"))
            if j >= len(units):
                continue
            is_j, d = jump_to(units[j], lab)
            if not is_j:
                continue
            k = next_unit(units, j, ("ins", "grp", "lab"))
            after = []
            while k < len(units) and units[k]["k"] == "lab":
                after.append(units[k]["name"])
                k = next_unit(units, k, ("ins", "grp", "lab"))
            if target not in after:
                continue
            if d and d != "nop":
                op, w, _ = regs(d)
                if w is None:
                    continue
                if x:
                    xo, xw, xr = regs(x)
                    if w in xr or (xw != w and not dead_after(units, k - 1, w)):
                        continue
                elif not dead_after(units, k - 1, w):
                    continue
            new = [{"k": "grp", "ins": ["%s\t%s,%s" % (INV[m.group(1)], m.group(2), lab), d]} if d else
                   {"k": "ins", "t": "%s\t%s,%s" % (INV[m.group(1)], m.group(2), lab)}]
            if x:
                new.append({"k": "ins", "t": x})
            block = [units[x] for x in labels] + [units[j]]
            if labels:
                # after the next unconditional jump (not the final return)
                b = next((x for x in range(j + 1, len(units)) if (first(units[x]) or "").startswith("j\t") and
                          first(units[x]) != "j\t$31"), None)
                if b is None:
                    continue
                units = units[:b + 1] + block + units[b + 1:]
            units[i:j + 1] = new
            changed = True
            break
    if first_mode:
        units = early_first(units, lab)
    return emit(units)


def sony_return(s, first_mode=False):
    """cc1 output -> one shared `jr ra; nop` per function."""
    out, pos, n = [], 0, 0
    for m in re.finditer(r"(?ms)^\t\.ent\t(\S+)\n.*?^\t\.end\t\1\n", s):
        n += 1
        out.append(s[pos:m.start()] + rewrite_function(m.group(0), n, first_mode))
        pos = m.end()
    out.append(s[pos:])
    return "".join(out)

#!/usr/bin/env python3
"""Rewrite the progress block of README.md (between <!-- progress:start --> and <!-- progress:end -->) from the
current state of src/ (tools/progress.py counts: a function is done when its C builds to the retail bytes).

  python3 -I tools/readme_progress.py          (run after a split / build, so asm/ is current)
"""
import datetime, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import progress as P

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

NAMES = {
    "boot": "SCUS_944.54: boot", "main": "MAIN.EXE: engine", "game": "GAME.BIN", "demo": "DEMO.BIN",
    "opn": "OPN.BIN: opening", "sop": "SOP.BIN", "crd": "CRD.BIN: credits",
}


def bar(f):
    n = int(round(f * 10))
    return "🟩" * n + "⬜" * (10 - n)


def main():
    c = P.counts()
    lines = []
    tot = {"n": 0, "b": 0, "dn": 0, "db": 0}
    for p in c:
        for cat in ("game", "lib"):
            tot["n"] += c[p].get(cat + "_n", 0)
            tot["b"] += c[p].get(cat + "_b", 0)
            tot["dn"] += c[p].get(cat + "_done_n", 0)
            tot["db"] += c[p].get(cat + "_done_b", 0)
    today = datetime.date.today().isoformat()
    lines.append("**Whole game: %.1f %% of the code matches byte for byte** (%d of %d bytes, %d of %d functions; %s)."
                 % (100.0 * tot["db"] / tot["b"], tot["db"], tot["b"], tot["dn"], tot["n"], today))
    lines.append("")
    lines.append("| Part | Functions | Bytes | Matching (bytes) |")
    lines.append("|---|---:|---:|---|")
    for title, progs, cat in P.PHASES:
        t = {"n": 0, "b": 0, "dn": 0, "db": 0}
        for p in (progs or ["main", "boot"]):
            t["n"] += c.get(p, {}).get(cat + "_n", 0)
            t["b"] += c.get(p, {}).get(cat + "_b", 0)
            t["dn"] += c.get(p, {}).get(cat + "_done_n", 0)
            t["db"] += c.get(p, {}).get(cat + "_done_b", 0)
        f = t["db"] / t["b"] if t["b"] else 0
        name = re.sub(r"^Phase (\w+)\s+", r"\1. ", title)
        lines.append("| %s | %d / %d | %d / %d | %s %.1f %% |" % (name, t["dn"], t["n"], t["db"], t["b"], bar(f),
                                                                100 * f))
    lines.append("")
    lines.append("<details>")
    lines.append("<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>")
    lines.append("")
    lines.append("| Program | Functions | Bytes | Matching (bytes) |")
    lines.append("|---|---:|---:|---|")
    order = ["boot", "main", "game", "demo", "opn", "sop", "crd"] + sorted(p for p in c if re.fullmatch(r"a0\w", p))
    for p in order:
        if p not in c:
            continue
        n, b = c[p].get("game_n", 0), c[p].get("game_b", 0)
        dn, db = c[p].get("game_done_n", 0), c[p].get("game_done_b", 0)
        f = db / b if b else 0
        name = NAMES.get(p, "%s.BIN: area overlay" % p.upper())
        lines.append("| %s | %d / %d | %d / %d | %s %.1f %% |" % (name, dn, n, db, b, bar(f), 100 * f))
    lines.append("")
    lines.append("</details>")
    block = "\n".join(lines)
    path = os.path.join(ROOT, "README.md")
    t = open(path).read()
    new = re.sub(r"(?s)(<!-- progress:start -->).*?(<!-- progress:end -->)",
                 lambda m: m.group(1) + "\n" + block + "\n" + m.group(2), t)
    if new == t and "<!-- progress:start -->" not in t:
        sys.exit("README.md has no progress markers")
    open(path, "w").write(new)
    print(lines[0])


if __name__ == "__main__":
    main()

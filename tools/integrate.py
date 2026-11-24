#!/usr/bin/env python3
"""The coordinator's end-of-round checklist in one command (AGENTS.md "Parallel rounds"). It never commits or pushes:
it prints what changed, and the coordinator commits it.

  python3 -I tools/integrate.py [--since REF] [--skip-clean] [--skip-sweeps] [-j N]
  python3 -I tools/integrate.py --only-since REF [-j N]

Steps (each one timed, a summary at the end):
 1. clean full build: `rm -rf build asm`, `tools/build.py` (29 programs), then `tools/build.py` again; reports the
    src/ files the first build's sync_src.py rewrote (and whether only whitespace / blank lines changed: the usual
    normalisation to commit) and whether the second build changed anything more (it should not);
 2. `tools/nearcopy.py --install` and `tools/dupsweep.py --install` over all programs (functions gained);
 3. full build again (29 OK expected);
 4. `tools/readme_progress.py` (README.md block rewritten) and `tools/progress.py --phases`;
 5. with --since REF: every commit of REF..HEAD is checked to link: the programs it touched (src/<prog>/, config/
    <prog>.yaml, config/aliases_<prog>.ld, config/symbol_addrs_<prog>.txt; include/, config/*.ld or the build tools:
    every program) are built at that commit in a temporary worktree (build/tmp_integrate_wt, with game/, include/pt
    and include/psyq symlinked from this checkout); the commits whose programs do not all build OK are reported, with
    "first" when that program built OK at the previous checked commit (the commit that broke it).
--only-since REF runs step 5 alone; --skip-clean starts at step 2 (with the current asm/), --skip-sweeps skips step 2.
"""
import argparse, glob, hashlib, os, re, shutil, subprocess, sys, time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

ALL_PATHS = ("include/", "config/undefined_syms.ld", "config/scratchpad.ld", "tools/build.py", "tools/cc.py",
             "tools/jtbl.py", "tools/sonyret.py", "tools/sync_src.py")
SUMMARY = []


def say(msg):
    print(msg, flush=True)
    SUMMARY.append(msg)


def run(cmd, cwd=ROOT, check=False):
    t = time.time()
    r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True)
    if check and r.returncode:
        sys.exit("FAILED: %s\n%s%s" % (" ".join(cmd), r.stdout[-4000:], r.stderr[-4000:]))
    return r, time.time() - t


def progs_all(root=ROOT):
    return sorted(os.path.basename(p)[:-5] for p in glob.glob(os.path.join(root, "config", "*.yaml")))


def src_snapshot():
    out = {}
    for f in glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True):
        out[os.path.relpath(f, ROOT)] = open(f, "rb").read()
    return out


def diff_snap(a, b):
    """(changed files, whitespace-only?) between two snapshots."""
    changed = sorted(k for k in set(a) | set(b) if a.get(k) != b.get(k))
    ws = all(k in a and k in b and re.sub(rb"\s+", b"", a[k]) == re.sub(rb"\s+", b"", b[k]) for k in changed)
    return changed, ws


def full_build(label, jobs, root=ROOT, progs=()):
    r, dt = run([sys.executable, "tools/build.py"] + list(progs) + ["-j", str(jobs)], cwd=root)
    lines = [l for l in r.stdout.splitlines() if re.match(r"\w+\s+(OK|DIFF)\s", l)]
    ok = [l.split()[0] for l in lines if l.split()[1] == "OK"]
    bad = [l.split()[0] for l in lines if l.split()[1] != "OK"]
    want = list(progs) or progs_all(root)
    missing = [p for p in want if p not in ok and p not in bad]
    if label:
        say("%s: %d / %d OK%s%s (%.0f s)" % (label, len(ok), len(want), ", DIFF: " + " ".join(bad) if bad else "",
                                             ", FAILED: " + " ".join(missing) if missing else "", dt))
        if missing:
            print(r.stdout[-3000:] + r.stderr[-3000:])
    return not bad and not missing, ok, bad + missing, r


def report_src(label, a, b):
    changed, ws = diff_snap(a, b)
    if not changed:
        say("%s: no src/ file changed" % label)
    else:
        say("%s: %d src/ file(s) changed (%s): %s" % (label, len(changed), "whitespace / blank lines only" if ws
            else "NOT whitespace only: read the diff", " ".join(changed)))
    return changed


def totals():
    import importlib, progress
    importlib.reload(progress)
    c = progress.counts()
    n = sum(v["game_done_n"] + v["lib_done_n"] for v in c.values())
    t = sum(v["game_n"] + v["lib_n"] for v in c.values())
    b = sum(v["game_done_b"] + v["lib_done_b"] for v in c.values())
    tb = sum(v["game_b"] + v["lib_b"] for v in c.values())
    return n, t, b, tb


def sweep(tool, jobs):
    before = src_snapshot()
    cmd = [sys.executable, "-I", "tools/%s.py" % tool, "--install"]
    if tool == "nearcopy":
        cmd += ["-j", str(jobs)]
    r, dt = run(cmd)
    after = src_snapshot()
    changed, _ = diff_snap(before, after)
    tail = [l for l in r.stdout.splitlines() if l.strip()][-3:]
    say("%s --install: %s (%.0f s)%s" % (tool, "files changed: " + " ".join(changed) if changed else "nothing installed",
                                         dt, "" if r.returncode == 0 else " EXIT %d" % r.returncode))
    for l in tail:
        print("    " + l)
    return changed


# ---- commit link check ----

def touched(paths, allp):
    progs = set()
    for p in paths:
        if p.startswith("config/eu/"):
            continue
        if any(p == q or (q.endswith("/") and p.startswith(q)) for q in ALL_PATHS):
            return set(allp)
        m = re.match(r"src/(\w+)/", p) or re.match(r"config/(\w+)\.yaml$", p) or \
            re.match(r"config/(?:aliases|symbol_addrs|undefined_syms_auto|undefined_funcs_auto)_(\w+)\.(?:ld|txt)$", p)
        if m and m.group(1) in allp:
            progs.add(m.group(1))
    return progs


def link_check(ref, jobs):
    shas = run(["git", "rev-list", "--reverse", "%s..HEAD" % ref], check=True)[0].stdout.split()
    if not shas:
        say("link check: no commit in %s..HEAD" % ref)
        return []
    allp = progs_all()
    wt = os.path.join(ROOT, "build", "tmp_integrate_wt")
    if os.path.exists(wt):
        run(["git", "worktree", "remove", "--force", wt])
        shutil.rmtree(wt, ignore_errors=True)
    run(["git", "worktree", "prune"])
    os.makedirs(os.path.dirname(wt), exist_ok=True)
    run(["git", "worktree", "add", "--detach", wt, shas[0]], check=True)
    bad, state = [], {}
    try:
        for i, sha in enumerate(shas):
            run(["git", "checkout", "-q", "-f", "--detach", sha], cwd=wt, check=True)   # the build's sync_src may have rewritten src/
            for link, target in (("game", "game"), ("include/pt", "include/pt"), ("include/psyq", "include/psyq")):
                dst = os.path.join(wt, link)
                if not os.path.lexists(dst) and os.path.exists(os.path.join(ROOT, target)):
                    os.symlink(os.path.join(ROOT, target), dst)
            files = run(["git", "diff-tree", "--no-commit-id", "--name-only", "-r", sha], check=True)[0].stdout.split()
            subj = run(["git", "log", "-1", "--format=%s", sha])[0].stdout.strip()
            progs = sorted(touched(files, allp))
            if not progs:
                print("  [%d/%d] %s no program touched: %s" % (i + 1, len(shas), sha[:9], subj[:70]), flush=True)
                continue
            ok, oks, fails, _ = full_build(None, jobs, root=wt, progs=progs)
            for p in oks:
                state[p] = True
            first = [p for p in fails if state.get(p, True)]
            for p in fails:
                state[p] = False
            print("  [%d/%d] %s %s %s: %s" % (i + 1, len(shas), sha[:9], "OK  " if ok else "FAIL",
                                               ",".join(progs) if len(progs) < 29 else "all programs",
                                               subj[:60]), flush=True)
            if not ok:
                bad.append((sha, subj, fails, first))
    finally:
        run(["git", "worktree", "remove", "--force", wt])
        shutil.rmtree(wt, ignore_errors=True)
        run(["git", "worktree", "prune"])
    if bad:
        say("link check %s..HEAD: %d of %d commits do not link:" % (ref, len(bad), len(shas)))
        for sha, subj, fails, first in bad:
            say("    %s %s: %s%s" % (sha[:9], subj[:60], " ".join(fails),
                                     " (first: %s)" % " ".join(first) if first else " (already broken before)"))
    else:
        say("link check %s..HEAD: all %d commits link" % (ref, len(shas)))
    return bad


def stale_tmp(hours=2):
    """leftovers of killed tool runs: build/tmp_regswap_* and tempfile's build/tmpXXXXXXXX untouched for more
    than `hours`."""
    now = time.time()
    for p in glob.glob(os.path.join(ROOT, "build", "tmp_regswap_*")) + \
            [q for q in glob.glob(os.path.join(ROOT, "build", "tmp*")) if re.fullmatch(r"tmp\w{8}", os.path.basename(q))]:
        try:
            if now - os.path.getmtime(p) > hours * 3600:
                shutil.rmtree(p, ignore_errors=True) if os.path.isdir(p) else os.remove(p)
                print("removed stale %s" % os.path.relpath(p, ROOT))
        except OSError:
            pass


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--since", help="check that every commit of REF..HEAD links (temporary worktree)")
    ap.add_argument("--only-since", metavar="REF", help="only the commit link check of REF..HEAD")
    ap.add_argument("--skip-clean", action="store_true", help="no clean full build first (use the current asm/)")
    ap.add_argument("--skip-sweeps", action="store_true", help="no nearcopy / dupsweep")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    a = ap.parse_args()
    a.since = a.since or a.only_since
    stale_tmp()
    t0 = time.time()
    ok_all = True
    if not a.only_since:
        start = src_snapshot()
        if not a.skip_clean:
            for d in ("build", "asm"):
                p = os.path.join(ROOT, d)
                if os.path.exists(os.path.join(p, "tmp_integrate_wt")):
                    run(["git", "worktree", "remove", "--force", os.path.join(p, "tmp_integrate_wt")])
                shutil.rmtree(p, ignore_errors=True)
            ok1 = full_build("clean full build", a.j)[0]
            first = src_snapshot()
            report_src("sync_src normalisation by the clean build", start, first)
            ok2 = full_build("second full build", a.j)[0]
            report_src("second build (should change nothing)", first, src_snapshot())
            ok_all = ok1 and ok2
        n0 = totals()
        if not a.skip_sweeps:
            sweep("nearcopy", a.j)
            sweep("dupsweep", a.j)
            ok3 = full_build("full build after the sweeps", a.j)[0]
            ok_all = ok_all and ok3
        n1 = totals()
        say("functions in C: %d / %d (%.1f %% of the bytes)%s" % (
            n1[0], n1[1], 100.0 * n1[2] / n1[3], ", +%d from the sweeps" % (n1[0] - n0[0]) if n1[0] != n0[0] else ""))
        readme = open(os.path.join(ROOT, "README.md")).read()
        run([sys.executable, "-I", "tools/readme_progress.py"], check=True)
        say("README.md progress block %s" % ("rewritten" if open(os.path.join(ROOT, "README.md")).read() != readme
                                            else "unchanged"))
        r, _ = run([sys.executable, "-I", "tools/progress.py", "--phases"], check=True)
        print(r.stdout)
        report_src("src/ changed by this run in all", start, src_snapshot())
    if a.since:
        bad = link_check(a.since, a.j)
        ok_all = ok_all and not bad
    st = run(["git", "status", "--short"])[0].stdout
    print("\n==== summary (%.0f min) ====" % ((time.time() - t0) / 60))
    for l in SUMMARY:
        print(l)
    if st.strip():
        print("uncommitted (review, then commit with explicit paths):\n" + st)
    sys.exit(0 if ok_all else 1)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""The native port against the reference emulator, frame by frame (docs/EMU.md).

Runs build/port/tomba2 (Linux, headless) and tools/emu_run.py (tools/psxemu) on the same input with the same dump layout,
then diffs each dumped frame: the displayed picture (with a diff image), VRAM (the differing regions), the GP0 packet list
(the first differing packet) and RAM (the differing ranges, named from build/main.elf).  It reports the first frame where
each differs and the BIN/ loads of both runs (a load at another frame means the two runs no longer agree on timing).

  python3 -I tools/emu_compare.py --route attract [--out DIR]          # title + attract demos, 6000 frames, every 100
  python3 -I tools/emu_compare.py --route a00                           # New Game -> A00 opening -> free play (10600)
  python3 -I tools/emu_compare.py --route title                         # boot -> title screen (400 frames, every 25)
  python3 -I tools/emu_compare.py --frames 3000 --every 50 --pad-script 400:start,600:cross [--ram-at 1000,2000]
      [--packets-at 1000] [--at 1234,1235] [--skip-port] [--skip-emu] [--python pypy3] [--port PATH]

--ram-at / --packets-at frames are taken from the port through gdb (tools/emu_portdump.py: the port is not changed) and
from the emulator directly.  --skip-port / --skip-emu reuse the dumps already in OUT/port or OUT/emu (a long emulator
run is kept and the port re-run after a fix).  The emulator runs under --python (default: this python3, or
$EMU_PYTHON; pypy3 is slower, docs/EMU.md).  OUT (default build/emu_compare/<route>) gets port/, emu/, diff/
(port | emulator | differing pixels in red, for each differing frame) and report.txt.
"""
import argparse
import os
import re
import shutil
import subprocess
import sys

import numpy as np
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
A00_SCRIPT = ("400:start,600:cross,800:cross,1000:cross,1200:cross,1400:start,6000:circle:10x50/60,9200:right:300,"
              "9550:cross:10,9600:right+cross:20,9700:left:300,10050:cross:10,10100:square:10,10200:up:100,10350:down:100")
ROUTES = {
    "title": dict(frames=400, every=25, pad=""),
    "attract": dict(frames=6000, every=100, pad=""),
    "a00": dict(frames=10600, every=100, pad=A00_SCRIPT),
    # attract demo 1 handed to the pad script at the A00 net wall (docs/PORT.md §0.4): onto the net, then up
    "net": dict(frames=2760, every=50, pad="2560:right:40,2600:right+cross:15,2615:right:30,2650:up:400",
                port="--keys-off --demo-takeover 2550", emu="--demo-takeover 2550"),
}


def find_python():
    # CPython: pypy3 (7.3.15 + numpy 1.26) ran the emulator 10x slower (0.5 M instructions/s against 5: every block is
    # exec'd Python source, which pypy's JIT does not warm up on); $EMU_PYTHON picks another interpreter
    return os.environ.get("EMU_PYTHON") or sys.executable


def run_port(a, out, extra_frames):
    os.makedirs(out, exist_ok=True)
    saves = os.path.join(out, "saves")
    shutil.rmtree(saves, ignore_errors=True)
    os.makedirs(saves)
    args = ["--frames", str(a.frames), "--dump-frames", out, "--dump-every", str(a.every), "--dump-vram",
            "--save-dir", saves]
    if a.pad_script:
        args += ["--pad-script", a.pad_script]
    args += a.port_args.split()   # e.g. --keys-off: the port's SPU key status as the emulator's (every voice off)
    log = os.path.join(out, "port_log.txt")
    if extra_frames:
        env = dict(os.environ, EMU_DUMP_FRAMES=",".join(map(str, sorted(extra_frames))), EMU_DUMP_DIR=out, EMU_PORT_LOG=log,
                   EMU_PORT_ARGS=" ".join("'%s'" % x for x in args))
        cmd = ["gdb", "-batch", "-x", os.path.join(ROOT, "tools", "emu_portdump.py"), a.port]
        subprocess.run(cmd, cwd=ROOT, env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    else:
        with open(log, "w") as f:
            subprocess.run([a.port] + args, cwd=ROOT, stdout=f, stderr=subprocess.STDOUT)


def run_emu(a, out, ram, pk):
    os.makedirs(out, exist_ok=True)
    cmd = [a.python, os.path.join(ROOT, "tools", "emu_run.py"), "--frames", str(a.frames), "--dump-frames", out,
           "--dump-every", str(a.every), "--dump-vram"]
    if a.pad_script:
        cmd += ["--pad-script", a.pad_script]
    if ram:
        cmd += ["--ram-at", ",".join(map(str, sorted(ram)))]
    if pk:
        cmd += ["--dump-packets", ",".join(map(str, sorted(pk)))]
    if a.at:
        cmd += ["--dump-at", a.at]
    if a.port_math:
        cmd += ["--port-math", a.port_math]
    cmd += a.emu_args.split()   # e.g. --demo-takeover F (with the same option in --port-args)
    with open(os.path.join(out, "emu_stdout.txt"), "w") as f:
        subprocess.run(cmd, cwd=ROOT, stdout=f, stderr=subprocess.STDOUT)


def load_png(path):
    return np.asarray(Image.open(path).convert("RGB"))


def regions(mask, tile=16, top=6):
    """Bounding boxes (x0, y0, x1, y1, pixels) of the connected groups of tiles holding differing pixels."""
    h, w = mask.shape
    th, tw = (h + tile - 1) // tile, (w + tile - 1) // tile
    pad = np.zeros((th * tile, tw * tile), bool)
    pad[:h, :w] = mask
    t = pad.reshape(th, tile, tw, tile).sum(axis=(1, 3))
    seen = np.zeros_like(t, bool)
    out = []
    for y in range(th):
        for x in range(tw):
            if t[y, x] and not seen[y, x]:
                st, box, n = [(y, x)], [x, y, x, y], 0
                seen[y, x] = True
                while st:
                    cy, cx = st.pop()
                    n += int(t[cy, cx])
                    box = [min(box[0], cx), min(box[1], cy), max(box[2], cx), max(box[3], cy)]
                    for ny, nx in ((cy + 1, cx), (cy - 1, cx), (cy, cx + 1), (cy, cx - 1)):
                        if 0 <= ny < th and 0 <= nx < tw and t[ny, nx] and not seen[ny, nx]:
                            seen[ny, nx] = True
                            st.append((ny, nx))
                out.append((box[0] * tile, box[1] * tile, min(w, (box[2] + 1) * tile) - 1, min(h, (box[3] + 1) * tile) - 1, n))
    out.sort(key=lambda r: -r[4])
    return out[:top], len(out)


def diff_image(path, p, e, mask):
    h = max(p.shape[0], e.shape[0])
    w = p.shape[1] + e.shape[1] + mask.shape[1] + 8
    img = np.zeros((h, w, 3), np.uint8)
    img[:p.shape[0], :p.shape[1]] = p
    img[:e.shape[0], p.shape[1] + 4:p.shape[1] + 4 + e.shape[1]] = e
    d = (np.stack([p, e]).mean(axis=0) * 0.3).astype(np.uint8)
    d[mask] = (255, 0, 0)
    x = p.shape[1] + e.shape[1] + 8
    img[:mask.shape[0], x:x + mask.shape[1]] = d
    Image.fromarray(img).save(path)


GP0 = [(0x20, 0x40, "poly"), (0x40, 0x60, "line"), (0x60, 0x80, "rect"), (0x80, 0xA0, "vram copy"), (0xA0, 0xC0, "cpu->vram"),
       (0xE1, 0xE7, "env"), (0x02, 0x03, "fill")]


def gp0_name(words):
    c = words[0] >> 24 if words else 0
    return next(("%s %02X" % (n, c) for lo, hi, n in GP0 if lo <= c < hi), "cmd %02X" % c)


def load_packets(path):
    out = []
    for line in open(path):
        p = line.split()
        if p and p[0].startswith("PK@"):
            out.append((int(p[0][3:], 16), [int(x, 16) for x in p[1:]]))
    return out


def symbols():
    """Sorted (address, name) of MAIN from build/main.elf (or config/symbol_addrs_main.txt)."""
    syms = {}
    elf = os.path.join(ROOT, "build", "main.elf")
    try:
        out = subprocess.run(["mipsel-linux-gnu-nm", elf], capture_output=True, text=True, check=True).stdout
        for line in out.splitlines():
            p = line.split()
            if len(p) == 3 and not p[2].startswith(".") and p[1] in "dDbBrRtTsS":
                syms.setdefault(int(p[0], 16), p[2])
    except (OSError, subprocess.CalledProcessError):
        for line in open(os.path.join(ROOT, "config", "symbol_addrs_main.txt")):
            m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", line)
            if m:
                syms.setdefault(int(m.group(2), 16), m.group(1))
    return sorted(syms.items())


def sym_at(syms, a):
    import bisect
    i = bisect.bisect_right(syms, (a, "\xff")) - 1
    if i < 0:
        return "?"
    s, n = syms[i]
    return "%s+0x%X" % (n, a - s) if a != s else n


def ram_ranges(p, e, gap=16):
    d = np.nonzero(p != e)[0]
    out = []
    for o in d:
        if out and o - out[-1][1] <= gap:
            out[-1][1] = o
            out[-1][2] += 1
        else:
            out.append([o, o, 1])
    return out


def ram_where(off):
    if off >= 0x200000:
        return "scratchpad", 0x1F800000 + off - 0x200000
    a = 0x80000000 + off
    if a < 0x80010000:
        return "kernel", a
    if a >= 0x801E0000:
        return "stack", a
    if a >= 0x80188000:
        return "overlay 0x80188000", a
    if a >= 0x80108F9C:
        return "overlay 0x80108F9C", a
    return "main", a


def compare(a, pdir, edir, ddir):
    os.makedirs(ddir, exist_ok=True)
    rep = []
    first = {}
    syms = symbols()

    def note(kind, f, text):
        first.setdefault(kind, (f, text))
        rep.append("frame %6d %-7s %s" % (f, kind, text))

    frames = sorted(int(m.group(1)) for n in os.listdir(edir) for m in [re.match(r"frame_(\d+)\.png$", n)] if m)
    nsame = 0
    for f in frames:
        pp, ep = os.path.join(pdir, "frame_%06d.png" % f), os.path.join(edir, "frame_%06d.png" % f)
        if not os.path.exists(pp):
            continue
        p, e = load_png(pp), load_png(ep)
        if p.shape != e.shape:
            note("frame", f, "size port %dx%d, emulator %dx%d" % (p.shape[1], p.shape[0], e.shape[1], e.shape[0]))
            continue
        mask = (p != e).any(axis=2)
        n = int(mask.sum())
        if n:
            regs, nr = regions(mask)
            note("frame", f, "%d pixels differ (%.1f%%) in %d regions: %s" % (n, 100.0 * n / mask.size, nr, "; ".join(
                "%d,%d-%d,%d (%d px)" % r for r in regs)))
            diff_image(os.path.join(ddir, "frame_%06d.png" % f), p, e, mask)
        else:
            nsame += 1
        pv, ev = os.path.join(pdir, "vram_%06d.png" % f), os.path.join(edir, "vram_%06d.png" % f)
        if os.path.exists(pv) and os.path.exists(ev):
            vp, ve = load_png(pv) >> 3, load_png(ev) >> 3
            vm = (vp != ve).any(axis=2)
            nv = int(vm.sum())
            if nv:
                regs, nr = regions(vm, 32)
                note("vram", f, "%d texels differ in %d regions: %s" % (nv, nr, "; ".join(
                    "x %d-%d y %d-%d (%d)" % (r[0], r[2], r[1], r[3], r[4]) for r in regs)))
    for f in sorted(int(m.group(1)) for n in os.listdir(edir) for m in [re.match(r"packets_(\d+)\.txt$", n)] if m):
        pp = os.path.join(pdir, "packets_%06d.txt" % f)
        if not os.path.exists(pp):
            continue
        P, E = load_packets(pp), load_packets(os.path.join(edir, "packets_%06d.txt" % f))
        k = next((i for i in range(min(len(P), len(E))) if P[i][1] != E[i][1]), None)
        if k is None and len(P) == len(E):
            rep.append("frame %6d packets %d, all equal" % (f, len(P)))
            continue
        if k is None:
            note("packets", f, "port %d, emulator %d packets; equal up to %d" % (len(P), len(E), min(len(P), len(E))))
            continue
        ndiff = sum(1 for i in range(min(len(P), len(E))) if P[i][1] != E[i][1])
        note("packets", f, "port %d, emulator %d packets, %d differ; first #%d: port %s @%08X [%s] / emulator %s @%08X [%s]" % (
            len(P), len(E), ndiff, k, gp0_name(P[k][1]), P[k][0], " ".join("%08x" % w for w in P[k][1]),
            gp0_name(E[k][1]), E[k][0], " ".join("%08x" % w for w in E[k][1])))
    for f in sorted(int(m.group(1)) for n in os.listdir(edir) for m in [re.match(r"ram_(\d+)\.bin$", n)] if m):
        pp = os.path.join(pdir, "ram_%06d.bin" % f)
        if not os.path.exists(pp):
            continue
        P = np.fromfile(pp, np.uint8)
        E = np.fromfile(os.path.join(edir, "ram_%06d.bin" % f), np.uint8)
        rr = ram_ranges(P[:len(E)], E[:len(P)])
        per = {}
        for o0, o1, n in rr:
            per[ram_where(o0)[0]] = per.get(ram_where(o0)[0], 0) + n
        rr_main = [r for r in rr if ram_where(r[0])[0] != "kernel"]
        rr_main.sort(key=lambda r: r[0])
        lines = []
        for o0, o1, n in rr_main[:a.ram_lines]:
            kind, ad = ram_where(o0)
            name = sym_at(syms, ad) if kind == "main" else kind
            lines.append("    %08X..%08X %5d bytes  %s" % (ad, ad + o1 - o0, n, name))
        note("ram", f, "%d differing bytes in %d ranges (%s)\n%s" % (
            sum(r[2] for r in rr), len(rr), ", ".join("%s %d" % kv for kv in sorted(per.items())), "\n".join(lines)))
    loads = []
    for name, path, rx in (("port", os.path.join(pdir, "port_log.txt"), r"frame (\d+): loading (\S+)"),
                           ("emulator", os.path.join(edir, "emu_log.txt"), r"load frame (\d+) (\S+)")):
        got = []
        if os.path.exists(path):
            got = re.findall(rx, open(path, errors="replace").read())
        loads.append((name, [(int(f), n) for f, n in got]))
    head = ["port %s vs emulator %s: %d frames compared, %d pixel-identical" % (pdir, edir, len(frames), nsame)]
    for kind in ("frame", "vram", "packets", "ram"):
        head.append("first %-7s difference: %s" % (kind, "frame %d: %s" % (first[kind][0], first[kind][1].split("\n")[0])
                                                    if kind in first else "none"))
    for name, l in loads:
        head.append("%-8s loads: %s" % (name, ", ".join("%d %s" % x for x in l)))
    if loads[0][1] != loads[1][1]:
        k = next((i for i in range(min(len(loads[0][1]), len(loads[1][1]))) if loads[0][1][i] != loads[1][1][i]), None)
        head.append("LOADS DIFFER%s" % ("" if k is None else " from #%d: port %s, emulator %s" % (k, loads[0][1][k], loads[1][1][k])))
    sp = os.path.join(edir, "emu_log.txt")
    if os.path.exists(sp):
        head.append("emulator: " + open(sp).readline().strip())
    return head + [""] + rep


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--route", choices=sorted(ROUTES))
    ap.add_argument("--frames", type=int)
    ap.add_argument("--every", type=int)
    ap.add_argument("--pad-script")
    ap.add_argument("--at", default="", help="extra emulator frame dumps (the port dumps multiples of --every only)")
    ap.add_argument("--ram-at", default="")
    ap.add_argument("--packets-at", default="")
    ap.add_argument("--ram-lines", type=int, default=40)
    ap.add_argument("--out")
    ap.add_argument("--port", default=os.path.join(ROOT, "build", "port", "tomba2"))
    ap.add_argument("--port-args", default="", help="extra port options, e.g. --keys-off (voices reported off as here)")
    ap.add_argument("--emu-args", default="", help="extra emulator options, e.g. --demo-takeover 2550")
    ap.add_argument("--python", default=None)
    ap.add_argument("--port-math", default="", help="emulator: the port's ratan2 / SquareRoot0 (step past a known difference)")
    ap.add_argument("--skip-port", action="store_true")
    ap.add_argument("--skip-emu", action="store_true")
    a = ap.parse_args()
    r = ROUTES.get(a.route, {})
    a.frames = a.frames or r.get("frames")
    a.every = a.every or r.get("every", 100)
    a.pad_script = r.get("pad", "") if a.pad_script is None else a.pad_script
    a.port_args = (r.get("port", "") + " " + a.port_args).strip()
    a.emu_args = (r.get("emu", "") + " " + a.emu_args).strip()
    if not a.frames:
        ap.error("--route or --frames")
    a.python = a.python or find_python()
    out = a.out or os.path.join(ROOT, "build", "emu_compare", a.route or "run")
    pdir, edir, ddir = os.path.join(out, "port"), os.path.join(out, "emu"), os.path.join(out, "diff")
    ram = {int(x) for x in a.ram_at.split(",") if x}
    pk = {int(x) for x in a.packets_at.split(",") if x}
    if not a.skip_port:
        shutil.rmtree(pdir, ignore_errors=True)
        run_port(a, pdir, ram | pk)
    if not a.skip_emu:
        shutil.rmtree(edir, ignore_errors=True)
        print("[emu_compare] emulator (%s), %d frames: a few minutes per 1000 frames" % (a.python, a.frames), flush=True)
        run_emu(a, edir, ram, pk)
    shutil.rmtree(ddir, ignore_errors=True)
    rep = compare(a, pdir, edir, ddir)
    with open(os.path.join(out, "report.txt"), "w") as f:
        f.write("\n".join(rep) + "\n")
    print("\n".join(rep[:12]))
    print("[emu_compare] full report: %s" % os.path.join(out, "report.txt"))


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Runs Tomba! 2 USA in the reference emulator (tools/psxemu, docs/EMU.md) with the native port's command line and dump
layout, so that its output can be diffed with build/port/tomba2's (tools/emu_compare.py).

  python3 -I tools/emu_run.py --frames 3000 --dump-frames DIR --dump-every 100 [--dump-vram] [--dump-ram]
      [--dump-packets all|F1,F2,...] [--pad-script 400:start,600:cross,...] [--disc game/usa.img] [-v]

Dumps in DIR (frame = vblank count, the port's port_frame; taken where the port takes them, after the vblank's callbacks):
  frame_NNNNNN.png    the displayed DISPENV area (port gpu.c port_gpu_frame: 15 / 24-bit, black while SetDispMask(0))
  vram_NNNNNN.png     1024x512, each 5-bit channel << 3 (the port's --dump-vram layout)
  ram_NNNNNN.bin      (--dump-ram, --ram-at F,...) 2 MB main RAM (0x80000000..0x801FFFFF) + 1 KB scratchpad (0x1F800000): 0x200400 bytes
  packets_NNNNNN.txt  every GP0 packet DrawOTag / DrawPrim sent during vblank NNNNNN, "PK@<KSEG0 address> <words>" per
                      line (the port's port_dump_packets format); written for the dumped frames with --dump-packets all
  emu_log.txt         the overlay loads (frame, file), stubs called, speed
CPython 3: about 5 M MIPS instructions/s (title 30+ frames/s, gameplay 5-7); pypy3 is 10x slower (docs/EMU.md).
"""
import argparse
import os
import struct
import sys
import time
import zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psxemu import machine as M  # noqa: E402


def write_png(path, w, h, rgb):
    raw = b"".join(b"\0" + rgb[y * w * 3:(y + 1) * w * 3] for y in range(h))

    def chunk(t, d):
        return struct.pack(">I", len(d)) + t + d + struct.pack(">I", zlib.crc32(t + d) & 0xFFFFFFFF)
    with open(path, "wb") as f:
        f.write(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 2, 0, 0, 0)) +
                chunk(b"IDAT", zlib.compress(raw, 1)) + chunk(b"IEND", b""))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--disc", default=None)
    ap.add_argument("--exe", default=None)
    ap.add_argument("--frames", type=int, required=True)
    ap.add_argument("--dump-frames", metavar="DIR")
    ap.add_argument("--dump-every", type=int, default=10)
    ap.add_argument("--dump-at", default="", help="extra frames to dump, comma separated")
    ap.add_argument("--dump-vram", action="store_true")
    ap.add_argument("--dump-ram", action="store_true", help="RAM of every dumped frame")
    ap.add_argument("--ram-at", default="", help="RAM dumps at these frames only")
    ap.add_argument("--dump-packets", default="", help="'all' (every dumped frame) or a frame list")
    ap.add_argument("--pad-script", default="")
    ap.add_argument("--demo-takeover", type=int, default=0, help="from this vblank the attract demo replays the pad script")
    ap.add_argument("--load-state", metavar="FILE", help="start from a state saved by --save-state (--frames stays absolute)")
    ap.add_argument("--save-state", metavar="FILE", help="save the state at the last frame")
    ap.add_argument("--port-math", default="", help="ratan2,SquareRoot0: the port's versions instead of retail libgte")
    ap.add_argument("-v", "--verbose", action="store_true")
    a = ap.parse_args(argv)
    m = M.Machine(disc=a.disc, exe=a.exe, verbose=a.verbose)
    if a.port_math:
        m.port_math(a.port_math.split(","))
    if a.load_state:
        m.load_state(a.load_state)
    m.pad_script = M.parse_pad_script(a.pad_script)
    m.demo_takeover = a.demo_takeover
    out = a.dump_frames
    if out:
        os.makedirs(out, exist_ok=True)
    at = {int(x) for x in a.dump_at.split(",") if x}
    pk_all = a.dump_packets == "all"
    pk = {int(x) for x in a.dump_packets.split(",") if x and x != "all"}
    ram_at = {int(x) for x in a.ram_at.split(",") if x}

    def dumped(f):
        return f in at or (a.dump_every > 0 and f % a.dump_every == 0)
    m.packet_frames = pk | ({f for f in range(a.frames + 1) if dumped(f)} if pk_all else set())
    t0 = time.time()
    last = [t0, 0]

    def on_vblank(m):
        f = m.frame
        if f % 100 == 0:
            now = time.time()
            print("[emu] frame %d: %.1f frames/s, %d M instructions, %d CD sectors" % (
                f, (f - last[1]) / max(now - last[0], 1e-6), m.cpu.icount // 1000000, m.cd_sectors), flush=True)
            last[0], last[1] = now, f
        if out and dumped(f):
            w, h, rgb = m.frame_rgb()
            write_png(os.path.join(out, "frame_%06d.png" % f), w, h, rgb)
            if a.dump_vram:
                write_png(os.path.join(out, "vram_%06d.png" % f), 1024, 512, m.vram_rgb())
        if out and ((a.dump_ram and dumped(f)) or f in ram_at):
            with open(os.path.join(out, "ram_%06d.bin" % f), "wb") as fh:
                fh.write(bytes(m.cpu.mem[:0x200400]))
        if out and (f - 1) in m.packets:
            write_packets(os.path.join(out, "packets_%06d.txt" % (f - 1)), m.packets.pop(f - 1))
    m.on_vblank = on_vblank
    f0, i0 = m.frame, m.cpu.icount
    m.run(a.frames)
    dt = time.time() - t0
    if a.save_state:
        m.on_vblank = None
        m.save_state(a.save_state)
    if out:
        for f, p in m.packets.items():
            write_packets(os.path.join(out, "packets_%06d.txt" % f), p)
    rep = ["frames %d in %.1f s: %.2f frames/s, %.2f M instructions/s (%s)" % (
               m.frame - f0, dt, (m.frame - f0) / max(dt, 1e-6), (m.cpu.icount - i0) / max(dt, 1e-6) / 1e6, sys.implementation.name),
           "spin vblanks %d" % m.spin_vblanks]
    rep += ["load frame %d %s" % x for x in m.loads]
    rep += ["stub %s %d" % x for x in sorted(m.stubs.items())]
    print("\n".join(rep[:2] + ["loads: " + ", ".join("%d %s" % x for x in m.loads)]))
    if out:
        with open(os.path.join(out, "emu_log.txt"), "w") as f:
            f.write("\n".join(rep) + "\n")


def write_packets(path, pk):
    with open(path, "w") as f:
        for addr, words in pk:
            f.write("PK@%08x %s\n" % (addr, " ".join("%08x" % w for w in words)))


if __name__ == "__main__":
    main()

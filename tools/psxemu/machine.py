"""The PlayStation around the CPU for Tomba! 2 USA (SCUS-94454): MAIN.EXE + the disc image + HLE of the BIOS and of the
Psy-Q 4.4 libraries, keyed by function address (tools/psxemu/syms/main_usa.csv, made by t2syms.py from our own names).

Adapted from Tombi-Decomp's tools/psxemu/machine.py (MIT, same author; see THIRD_PARTY_NOTICES.md).  T1's machine HLE'd the
BIOS + libgpu / libcd of the first game; this one draws the HLE boundary where the native port draws its shims (port/shims),
with the same semantics, so that a frame-by-frame comparison with build/port/tomba2 isolates the port's native code and its
shim *implementations* (GPU rasterizer, GTE, libgte / libc / libgpu helpers) and not a timing model:

  * every game function (MAIN and the overlays) runs as retail MIPS code (cpu.py, block compiler);
  * the "pure" Psy-Q libraries (libc, libc2, libgte, libsn, libgpu's primitive helpers: t2syms.py, port gen_t2.py
    PURE_LIBS / PURE_GPU) run as retail MIPS code too, although the port replaces several of them by C (rsin, ratan2,
    RotTransPers, MulMatrix0, SetDrawMode, memcpy, rand ...): their retail behaviour is the reference;
  * the hardware libraries (libgpu VRAM / OT / environments, libetc VSync and callbacks, libapi threads / events, libcd,
    libpad, libsnd / libspu, libcard, libpress) are HLE'd here exactly as the port's shims do it, and every other hardware
    library function returns 0 (the port's logged stubs);
  * timing is the port's: a vblank happens on VSync(0 / n) and when a loop of interpreted code spins on memory
    (mips_interp.c is_spin), the vblank runs the pad, the virtual disc (4 data sectors, 2.5 XA sectors per vblank), the
    VSync callbacks and event handler, then the frame dump; the frame number is the vblank count (port_frame);
  * the disc is the port's virtual disc (shims/cd_virtual.inc): CdSearchFile gives each file a made-up position (from LBA
    1000, in lookup order, 16 sectors apart), the sectors come from the raw image through the ISO 9660 directory.

Not emulated: sound output (libsnd / libspu keep only the ids and allocations the game reads back), MDEC (movies end at
once: StGetNext reports a frame past the end, as in the port), memory card contents (an empty formatted card).
"""
import csv
import os
import struct
import sys

from . import cpu as _cpu
from . import gpu as _gpu

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SYMS = os.path.join(os.path.dirname(os.path.abspath(__file__)), "syms", "main_usa.csv")
MAIN_SHA1_USA = "f41c4065"          # prefix of the USA MAIN.EXE SHA-1 (port main_port.c MAIN_SHA1_USA)
CD_FIRST_LBA = 1000
SPIN_MAX = 32
FAKE_ST = 0x80000F00                # StGetNext's fake sector header + frame (the port keeps them in host memory)
TCB_TABLE = 0x80000C00
THREAD_RET = 0x80000E40             # return address of a thread's entry: it ended (the port: treated as exitTask)              # BIOS TCB table the game pokes through 0x110 (port: a dummy host table)

PAD_NAMES = {"select": 0x0001, "start": 0x0008, "up": 0x0010, "right": 0x0020, "down": 0x0040, "left": 0x0080,
             "l2": 0x0100, "r2": 0x0200, "l1": 0x0400, "r1": 0x0800, "triangle": 0x1000, "circle": 0x2000,
             "cross": 0x4000, "square": 0x8000}


def bcd(b):
    return (b >> 4) * 10 + (b & 15)


def tobcd(v):
    return ((v // 10) << 4) | (v % 10)


def lba_to_loc(lba):
    lba += 150
    return bytes([tobcd(lba // 4500), tobcd(lba // 75 % 60), tobcd(lba % 75), 0])


def loc_to_lba(p):
    return (bcd(p[0]) * 60 + bcd(p[1])) * 75 + bcd(p[2]) - 150


def parse_pad_script(s):
    """The port's --pad-script syntax (shims/pad.c): FRAME:BUTTONS[:LEN[xCOUNT/PERIOD]],... -> [(frame, len, count, period, mask)]."""
    out = []
    for ent in [e for e in (s or "").split(",") if e]:
        parts = ent.split(":")
        f = int(parts[0])
        mask = 0
        for b in parts[1].split("+") if len(parts) > 1 else []:
            mask |= int(b, 16) if b.lower().startswith("0x") else PAD_NAMES[b.lower()]
        ln, count, period = 4, 1, 0
        if len(parts) > 2:
            rest = parts[2]
            if "x" in rest:
                a, b = rest.split("x", 1)
                ln = int(a) if a else 4
                if "/" in b:
                    count, period = (int(v) for v in b.split("/", 1))
                else:
                    count = int(b)
            else:
                ln = int(rest)
        out.append((f, ln, count, period if period > 0 else (ln if ln > 0 else 1), mask))
    return out


class Disc:
    """A raw (2352) or cooked (2048) image with its ISO 9660 directory."""
    def __init__(self, path):
        self.f = open(path, "rb")
        self.f.seek(0)
        head = self.f.read(16)
        if head[:12] == b"\x00" + b"\xff" * 10 + b"\x00":
            self.ssize = 2352
            self.f.seek(16 * 2352)
            self.doff = 16 if self.f.read(16)[15] == 1 else 24
        else:
            self.ssize, self.doff = 2048, 0
        self.files = {}
        self._walk(*self._root(), "")

    def data(self, lba):
        self.f.seek(lba * self.ssize + self.doff)
        return self.f.read(2048)

    def raw(self, lba):
        self.f.seek(lba * self.ssize)
        return self.f.read(self.ssize)

    def _root(self):
        pvd = self.data(16)
        return struct.unpack_from("<I", pvd, 156 + 2)[0], struct.unpack_from("<I", pvd, 156 + 10)[0]

    def _walk(self, lba, size, prefix):
        data = b"".join(self.data(lba + i) for i in range((size + 2047) // 2048))
        o = 0
        while o < len(data):
            n = data[o]
            if n == 0:
                o = (o // 2048 + 1) * 2048
                continue
            flags = data[o + 25]
            name = data[o + 33:o + 33 + data[o + 32]]
            elba, esize = struct.unpack_from("<I", data, o + 2)[0], struct.unpack_from("<I", data, o + 10)[0]
            if name not in (b"\0", b"\1"):
                nm = name.decode("ascii", "replace").split(";")[0].upper()
                if flags & 2:
                    self._walk(elba, esize, prefix + nm + "/")
                else:
                    self.files[prefix + nm] = (elba, esize)
            o += n

    def read_file(self, rel):
        lba, size = self.files[rel]
        return b"".join(self.data(lba + i) for i in range((size + 2047) // 2048))[:size]


class Machine:
    def __init__(self, disc=None, exe=None, verbose=False):
        self.verbose = verbose
        self.cpu = c = _cpu.CPU()
        self.gpu = _gpu.GPU()
        self.disc = Disc(disc or os.path.join(ROOT, "game", "usa.img"))
        self.names, self.lib = {}, {}
        with open(SYMS, newline="") as f:
            for r in csv.DictReader(l for l in f if not l.startswith("#")):
                a = int(r["address"], 16)
                self.names.setdefault(r["name"], a)
                self.lib[a] = (r["name"], r["lib"], r["pure"] == "1")
        self.io = {0x1F801814: 0x1C802000, 0x1F801070: 0}      # port init_io: GPUSTAT ready, I_STAT
        c.io_read = lambda cpu, a, n: self.io.get(a & ~3, 0) >> (8 * (a & 3)) & ((1 << (8 * n)) - 1)
        c.io_write = self._io_write
        self.frame = 0                  # port_frame: vblanks so far
        self.max_frames = None
        self.on_vblank = None           # fn(machine) after the callbacks (the port's port_gpu_vblank: frame dumps)
        self.packet_frames = set()      # frames whose GP0 packets are recorded (self.packets[frame])
        self.packets = {}
        self.stubs = {}
        self.vsync_cb = 0
        self.vsync_cbs = [0, 0, 0, 0]
        self.vsync_event_fn = 0
        self.vsync_last = 0
        self.events = [None] * 32       # [desc, spec, pending]
        self.threads = {}               # slot -> (regs, hi, lo, pc)
        self.cur_th = 0
        self.disp_mask = 0
        self.drawenv = bytes(0x5C)
        self.dispenv = bytes(0x14)
        self.pad_script = []
        self.pad_buttons = 0
        self.pad_buf = [0, 0]
        self.pad_started = False
        self.cd_files = []              # [name, lba, nsec, size, img_lba]
        self.cd_next = CD_FIRST_LBA
        self.cd_pos = 0
        self.cd_target, self.cd_target_pending = 0, False
        self.cd_ready_cb = self.cd_sync_cb = self.cd_read_cb = self.cd_data_cb = 0
        self.cd_mode, self.cd_last_com = 0x80, 0
        self.cd_reading = False
        self.cd_sector = bytes(2352)
        self.cd_sector_off = 0
        self.cd_result = bytes(8)
        self.cd_xa_half = 0
        self.cd_sectors = 0
        self.loads = []                 # (frame, file) of every BIN/ file read from its first sector
        self.snd = dict(vabs={}, seqs={}, spu_next=0x1010, sep=0, spu_alloc=0x1010)
        self.spin_vblanks = 0
        data = self.disc.read_file("MAIN.EXE") if exe is None else open(exe, "rb").read()
        self.load_exe(data)
        c.w32(0x110, TCB_TABLE)
        self.install_hle()
        c.spin_hook = self._spin
        c.bios = self.bios
        c.hle[THREAD_RET] = self.thread_returned
        self.bios_calls = {}

    def bios(self, c, table, num):
        """A BIOS call that no HLE'd library function made (the port has no BIOS: these are the retail library
        wrappers the port replaces by name, so they cannot be reached there): logged, returns 0."""
        k = "%02X:%02X" % (table, num)
        self.bios_calls[k] = self.bios_calls.get(k, 0) + 1
        if self.bios_calls[k] == 1 and self.verbose:
            print("[emu] BIOS %s from %08X frame %d" % (k, c.R[31], self.frame))
        c.R[2] = 0

    # ------------------------------------------------------------------ save states (emu_run.py --save-state / --load-state)
    SKIP = {"cpu", "gpu", "disc", "on_vblank", "verbose"}

    def save_state(self, path):
        import pickle
        c, g = self.cpu, self.gpu
        st = {k: v for k, v in self.__dict__.items() if k not in self.SKIP and not callable(v)}
        st["_cpu"] = dict(mem=bytes(c.mem), R=list(c.R), hi=c.hi, lo=c.lo, pc=c.pc, cop0=list(c.cop0), icount=c.icount,
                          gte=(list(c.gte.d), list(c.gte.c), c.gte.flag))
        st["_gpu"] = dict(vram=g.vram.tobytes(), state=(g.tpage, g.tw, g.clip, g.ofs, g.set_mask, g.dtd))
        with open(path, "wb") as f:
            pickle.dump(st, f)

    def load_state(self, path):
        """Only between runs (a state is saved at a vblank, outside any nested call)."""
        import pickle
        import numpy as np
        with open(path, "rb") as f:
            st = pickle.load(f)
        c, g = self.cpu, self.gpu
        cs, gs = st.pop("_cpu"), st.pop("_gpu")
        c.mem[:] = cs["mem"]
        c.R[:] = cs["R"]
        c.hi, c.lo, c.pc, c.icount = cs["hi"], cs["lo"], cs["pc"], cs["icount"]
        c.cop0[:] = cs["cop0"]
        c.gte.d[:], c.gte.c[:], c.gte.flag = cs["gte"]
        c.blocks.clear()
        g.vram[:] = np.frombuffer(gs["vram"], dtype=np.uint16).reshape(g.vram.shape)
        g.tpage, g.tw, g.clip, g.ofs, g.set_mask, g.dtd = gs["state"]
        self.__dict__.update(st)

    # ------------------------------------------------------------------ loading
    def load_exe(self, d):
        import hashlib
        h = hashlib.sha1(d).hexdigest()
        if not h.startswith(MAIN_SHA1_USA):
            print("[emu] warning: MAIN.EXE SHA-1 %s is not the USA one" % h, file=sys.stderr)
        pc, gp, taddr, tsize = struct.unpack_from("<4I", d, 0x10)
        spb, spo = struct.unpack_from("<2I", d, 0x30)
        self.cpu.write(taddr, d[0x800:0x800 + tsize])
        self.cpu.R[28] = gp
        self.cpu.R[29] = (spb + spo) & 0xFFFFFFFF if spb else 0x801FFFF0
        self.cpu.pc = pc
        self.cpu.R[31] = _cpu.STOP

    def _io_write(self, cpu, a, v, n):
        al = a & ~3
        sh = 8 * (a & 3)
        mask = ((1 << (8 * n)) - 1) << sh
        self.io[al] = (self.io.get(al, 0) & ~mask) | ((v << sh) & mask)
        return True

    # ------------------------------------------------------------------ HLE table
    def install_hle(self):
        h = self.cpu.hle
        impl = {}
        for n in dir(self):
            if n.startswith("h_"):
                impl[n[2:]] = getattr(self, n)
        consts = {   # the port's shims that only return a value
            "ResetGraph": 0, "SetGraphDebug": 0, "GetGraphDebug": 0, "SetGraphQueue": 0, "DrawSync": 0, "DrawSyncCallback": 0,
            "GetGraphType": 0, "GetODE": 0, "_GPU_ResetCallback": 0,
            "EnterCriticalSection": 1, "ExitCriticalSection": 0, "EnableEvent": 1, "DisableEvent": 1, "WaitEvent": 1,
            "SetRCnt": 1, "StartRCnt": 1, "StopRCnt": 1, "ResetRCnt": 1, "GetRCnt": 0, "GetIntrMask": 0, "SetIntrMask": 0,
            "SetCustomExitFromException": 0, "ReturnFromException": 0, "HookEntryInt": 0, "ResetEntryInt": 0, "FlushCache": 0,
            "GetGp": 0, "SysEnqIntRP": 0, "SysDeqIntRP": 0, "ChangeClearRCnt": 0, "ChangeClearPAD": 0, "SetVideoMode": 1,
            "GetVideoMode": 1, "InitHeap": 0, "ResetCallback": 0, "StopCallback": 0, "RestartCallback": 0, "DMACallback": 0,
            "InterruptCallback": 0, "_96_remove": 0,
            "CdInit": 1, "CdReset": 1, "CdStatus": 2, "CdSetDebug": 0, "CdFlush": 0, "CdDataSync": 0, "CdReadBreak": 0,
            "CdMix": 1, "CdRead2": 1, "StSetRing": 0, "StClearRing": 0, "StUnSetRing": 0, "StFreeRing": 0, "StSetStream": 0,
            "StSetMask": 0,
            "PadChkVsync": 0, "PadInfoAct": 0, "PadInfoComb": 0, "PadSetAct": 1, "PadSetActAlign": 1, "PadSetMainMode": 1,
            "PadChkMtap": 0,
            "SpuIsTransferCompleted": 1, "SsVabTransCompleted": 1, "SpuClearReverbWorkArea": 1, "SsSepClose": 0, "SpuFree": 0,
            "_card_status": 1, "_card_wait": 1, "_card_chan": 0, "_new_card": 0, "InitCARD": 0, "StartCARD": 1, "StopCARD": 1,
            "StopCARD2": 1, "_bu_init": 0, "_patch_card2": 0, "_patch_card": 0, "_ExitCard": 0, "InitCARD2": 1, "StartCARD2": 1,
            "_copy_memcard_patch": 0,
        }
        for a, (n, lib, pure) in self.lib.items():
            if n in impl:
                h[a] = impl[n]
            elif n in consts:
                h[a] = self._ret(consts[n])
            elif not pure:
                h[a] = self._stub(n)

    # ------------------------------------------------------------------ the port's own math (emu_run.py --port-math)
    def port_math(self, names):
        """Replaces retail libgte functions by Python copies of the port's shims (port/shims/psyq.c), to step past a
        known difference and find the next one: ratan2 (binary search on the port's sine table), SquareRoot0 (exact
        integer square root)."""
        import math
        tab = []
        for i in range(1025):
            x = i * (math.pi / 2048.0)
            t = s = x
            for k in range(1, 12):
                t *= -x * x / ((2 * k) * (2 * k + 1))
                s += t
            tab.append(int(s * 4096.0 + 0.5))

        def rsin(a):
            a &= 4095
            return tab[a] if a < 1024 else tab[2048 - a] if a < 2048 else -tab[a - 2048] if a < 3072 else -tab[4096 - a]

        def ratan2(c):
            y, x = _cpu.s32(c.R[4]), _cpu.s32(c.R[5])
            ay, ax = abs(y), abs(x)
            if not ax and not ay:
                c.R[2] = 0
                return
            sw = ay > ax
            num, den = (ax, ay) if sw else (ay, ax)
            lo, hi = 0, 512
            while lo < hi:
                m = (lo + hi + 1) // 2
                if rsin(m) * den <= rsin(m + 1024) * num:
                    lo = m
                else:
                    hi = m - 1
            a = 1024 - lo if sw else lo
            a = 2048 - a if x < 0 else a
            c.R[2] = (-a if y < 0 else a) & 0xFFFFFFFF

        def sqrt0(c):
            c.R[2] = math.isqrt(c.R[4])
        impl = {"ratan2": ratan2, "SquareRoot0": sqrt0}
        for n in names:
            self.cpu.hle[self.names[n]] = impl[n]

    def _ret(self, v):
        def f(c):
            c.R[2] = v & 0xFFFFFFFF
        return f

    def _stub(self, name):
        def f(c):
            self.stubs[name] = self.stubs.get(name, 0) + 1
            if self.stubs[name] == 1 and self.verbose:
                print("[emu] stub %s frame %d" % (name, self.frame))
            c.R[2] = 0
        return f

    def call(self, fn, *args):
        if fn:
            self.cpu.call(fn, *args)

    # ------------------------------------------------------------------ vblank (port psyq.c port_vblank)
    def vblank(self):
        self.frame += 1
        self.pad_vblank()
        self.cd_vblank()
        for f in self.vsync_cbs:
            self.call(f)
        self.call(self.vsync_event_fn)
        self.call(self.vsync_cb)
        if self.on_vblank:
            self.on_vblank(self)
        if self.max_frames and self.frame >= self.max_frames:
            raise StopRun()

    def _spin(self):
        self.spin_vblanks += 1
        self.vblank()

    def run(self, frames):
        """Runs until vblank `frames` (absolute); the CPU can be run on later (or saved) from there."""
        self.max_frames = frames
        self._resume = None
        try:
            self.cpu.run()
        except StopRun:
            if self._resume is not None:        # stopped inside VSync: resume at its return address
                self.cpu.pc = self._resume

    def h_VSync(self, c):
        mode = _cpu.s32(c.R[4])
        if mode < 0:
            c.R[2] = self.frame
            return
        if mode == 1:
            c.R[2] = (self.frame - self.vsync_last) & 0xFFFFFFFF
            return
        try:
            for _ in range(1 if mode == 0 else mode):
                self.vblank()
        except StopRun:
            c.R[2] = (self.frame - self.vsync_last) & 0xFFFFFFFF
            self.vsync_last = self.frame
            self._resume = c.R[31]
            raise
        c.R[2] = (self.frame - self.vsync_last) & 0xFFFFFFFF
        self.vsync_last = self.frame

    def h_VSyncCallback(self, c):
        self.vsync_cb = c.R[4]
        c.R[2] = 0

    def h_VSyncCallbacks(self, c):
        if c.R[4] < 4:
            self.vsync_cbs[c.R[4]] = c.R[5]
        c.R[2] = 0

    # ------------------------------------------------------------------ libapi: events, threads
    def h_OpenEvent(self, c):
        desc, spec, func = c.R[4], c.R[5], c.R[7]
        if desc in (0xF2000003, 0xF0000001) and func:
            self.vsync_event_fn = func
        for i in range(32):
            if self.events[i] is None:
                self.events[i] = [desc, spec, 0]
                c.R[2] = 0xF1000000 | i
                return
        c.R[2] = 0xF1000000 | (desc & 0xFF)

    def h_CloseEvent(self, c):
        ev = c.R[4]
        if ev & 0xFFFFFF00 == 0xF1000000 and (ev & 0xFF) < 32:
            self.events[ev & 0xFF] = None
        c.R[2] = 1

    def h_TestEvent(self, c):
        ev = c.R[4]
        i = ev & 0xFF
        e = self.events[i] if ev & 0xFFFFFF00 == 0xF1000000 and i < 32 else None
        if not e or not e[2]:
            c.R[2] = 0
            return
        e[2] = 0
        c.R[2] = 1

    def deliver(self, desc, spec, on=1):
        for e in self.events:
            if e and e[0] == desc and e[1] == spec:
                e[2] = on

    def h_DeliverEvent(self, c):
        self.deliver(c.R[4], c.R[5])

    def h_UnDeliverEvent(self, c):
        self.deliver(c.R[4], c.R[5], 0)

    def h_OpenTh(self, c):
        for i in range(1, 17):
            if i not in self.threads:
                regs = [0] * 32
                regs[29] = regs[30] = c.R[5]
                regs[28] = c.R[6]
                regs[31] = THREAD_RET
                self.threads[i] = (regs, 0, 0, c.R[4])
                c.R[2] = 0xFF000000 | i
                return
        raise _cpu.EmuError("OpenTh: out of threads")

    def h_CloseTh(self, c):
        n = c.R[4] & 0xFF
        if 1 <= n <= 16:
            self.threads.pop(n, None)
        c.R[2] = 1

    def thread_returned(self, c):
        print("[emu] thread %d returned (frame %d)" % (self.cur_th, self.frame), file=sys.stderr)
        self.threads.pop(self.cur_th, None)
        c.R[4] = 0xFF000000
        self.h_ChangeTh(c)

    def h_ChangeTh(self, c):
        n = c.R[4] & 0xFF
        if n > 16 or (n and n not in self.threads):
            print("[emu] ChangeTh(%08X): no such thread" % c.R[4], file=sys.stderr)
            c.R[2] = 1
            return
        if n == self.cur_th:
            c.R[2] = 1
            return
        if self.cur_th == 0 or self.cur_th in self.threads:     # not a thread that closed itself (CloseTh + ChangeTh)
            saved = list(c.R)
            saved[2] = 1
            self.threads[self.cur_th] = (saved, c.hi, c.lo, c.R[31])
        regs, hi, lo, pc = self.threads[n]
        c.R[:] = regs
        c.hi, c.lo = hi, lo
        self.cur_th = n
        c.pc_override = pc

    # ------------------------------------------------------------------ libgpu (port shims/gpu.c)
    def _rect(self, a):
        return struct.unpack("<4h", self.cpu.read(a, 8))

    def h_LoadImage(self, c):
        x, y, w, h = self._rect(c.R[4])
        if w > 0 and h > 0:
            self.gpu.load_image(x & 0x3FF, y & 0x1FF, w, h, c.read(c.R[5], w * h * 2))
        c.R[2] = 0
    h_LoadImage2 = h_LoadImage

    def h_StoreImage(self, c):
        x, y, w, h = self._rect(c.R[4])
        if w > 0 and h > 0:
            c.write(c.R[5], self.gpu.store_image(x & 0x3FF, y & 0x1FF, w, h))
        c.R[2] = 0
    h_StoreImage2 = h_StoreImage

    def h_MoveImage(self, c):
        x, y, w, h = self._rect(c.R[4])
        if w > 0 and h > 0:
            self.gpu.move(x & 0x3FF, y & 0x1FF, c.R[5] & 0x3FF, c.R[6] & 0x1FF, w, h)
        c.R[2] = 0
    h_MoveImage2 = h_MoveImage

    def h_ClearImage(self, c):
        x, y, w, h = self._rect(c.R[4])
        self.gpu.fill(x, y, w, h, _gpu.rgb15((c.R[5] & 0xFF) | (c.R[6] & 0xFF) << 8 | (c.R[7] & 0xFF) << 16))
        c.R[2] = 0
    h_ClearImage2 = h_ClearImage

    def h_LoadClut(self, c, w=256):
        x, y = c.R[5], c.R[6]
        self.gpu.load_image(x & 0x3FF, y & 0x1FF, w, 1, c.read(c.R[4], w * 2))
        c.R[2] = ((y << 6) | ((x >> 4) & 0x3F)) & 0xFFFF

    def h_LoadClut2(self, c):
        self.h_LoadClut(c, 16)

    def h_SetDispMask(self, c):
        self.disp_mask = c.R[4]

    def h_PutDrawEnv(self, c):
        e = c.read(c.R[4], 0x5C)
        self.drawenv = e
        cx, cy, cw, ch, ox, oy, twx, twy, tww, twh, tpage = struct.unpack_from("<11h", e, 0)
        g = self.gpu
        x1, y1 = max(cx, 0), max(cy, 0)
        x2, y2 = min(cx + cw - 1, 1023), min(cy + ch - 1, 511)
        g.clip = (x1, y1, x2, y2)
        g.ofs = (ox, oy)
        g.tpage = (tpage & 0x9FF) | (0x200 if e[22] else 0) | (0x400 if e[23] else 0)
        g.dtd = bool(e[22])
        g.tw = ((-tww & 0xFF) >> 3 if tww else 0, (-twh & 0xFF) >> 3 if twh else 0, (twx >> 3) & 31, (twy >> 3) & 31)
        if e[24]:
            g.fill(x1, y1, x2 - x1 + 1, y2 - y1 + 1, _gpu.rgb15(e[25] | e[26] << 8 | e[27] << 16))
        c.R[2] = c.R[4]

    def h_GetDrawEnv(self, c):
        c.write(c.R[4], self.drawenv)
        c.R[2] = c.R[4]

    def h_PutDispEnv(self, c):
        self.dispenv = c.read(c.R[4], 0x14)
        c.R[2] = c.R[4]

    def h_GetDispEnv(self, c):
        c.write(c.R[4], self.dispenv)
        c.R[2] = c.R[4]

    def h_ClearOTagR(self, c):
        ot, n = c.R[4] | 0x80000000, c.R[5]
        for i in range(n - 1, 0, -1):
            c.w32(ot + 4 * i, (ot + 4 * (i - 1)) & 0xFFFFFF)
        if n > 0:
            c.w32(ot, 0xFFFFFF)
        c.R[2] = ot

    def h_ClearOTag(self, c):
        ot, n = c.R[4] | 0x80000000, c.R[5]
        for i in range(n - 1):
            c.w32(ot + 4 * i, (ot + 4 * (i + 1)) & 0xFFFFFF)
        if n > 0:
            c.w32(ot + 4 * (n - 1), 0xFFFFFF)
        c.R[2] = ot

    def h_DrawOTag(self, c):
        a = c.R[4] & 0xFFFFFF
        mem = c.mem
        pk = []
        seen = 0
        while seen < 200000:
            seen += 1
            o = a & 0x1FFFFF
            tag = struct.unpack_from("<I", mem, o)[0]
            n = (tag >> 24) & 0x7F
            if n:
                pk.append((a | 0x80000000, list(struct.unpack_from("<%dI" % n, mem, o + 4))))
            nxt = tag & 0xFFFFFF
            if nxt == 0xFFFFFF:
                break
            a = nxt
        if self.frame in self.packet_frames:
            self.packets.setdefault(self.frame, []).extend(pk)
        self.gpu.run_packets([w for _, w in pk])
    h_DrawOTag2 = h_DrawOTag

    def h_DrawOTagEnv(self, c):
        ot = c.R[4]
        c.R[4] = c.R[5]
        self.h_PutDrawEnv(c)
        c.R[4] = ot
        self.h_DrawOTag(c)

    def h_DrawPrim(self, c):
        o = c.R[4]
        n = c.r32(o) >> 24
        if n:
            w = [c.r32(o + 4 + 4 * i) for i in range(n)]
            if self.frame in self.packet_frames:
                self.packets.setdefault(self.frame, []).append((o | 0x80000000, w))
            self.gpu.run_packets([w])

    def h_GPU_cw(self, c):
        self.gpu.run_packets([[c.R[4]]])
        c.R[2] = 0

    def frame_rgb(self):
        """The displayed area (DISPENV.disp; 15 / 24-bit) as (w, h, RGB bytes): port gpu.c port_gpu_frame."""
        import numpy as np
        x, y, w, h = struct.unpack_from("<4h", self.dispenv, 0)
        rgb24 = self.dispenv[0x11]
        W = w if w > 0 else 320
        H = h if h > 0 else 240
        W, H = min(W, 1024), min(H, 512)
        if not self.disp_mask:
            return W, H, bytes(W * H * 3)
        v = self.gpu.vram
        rows = (y + np.arange(H)) & 511
        if rgb24:
            raw = v[rows].astype("<u2").view(np.uint8).reshape(H, 2048)
            bx = (x * 2 + np.arange(W)[:, None] * 3 + np.arange(3)[None, :]) & 2047
            return W, H, raw[:, bx].reshape(H, W * 3).tobytes()
        cols = (x + np.arange(W)) & 1023
        blk = v[rows][:, cols].astype(np.uint32)
        r, g, b = blk & 31, (blk >> 5) & 31, (blk >> 10) & 31
        out = np.stack([r << 3 | r >> 2, g << 3 | g >> 2, b << 3 | b >> 2], axis=2).astype(np.uint8)
        return W, H, out.tobytes()

    def vram_rgb(self):
        """VRAM as the port's --dump-vram PNG: 1024x512, each 5-bit channel << 3."""
        import numpy as np
        v = self.gpu.vram.astype(np.uint32)
        return np.stack([(v & 31) << 3, ((v >> 5) & 31) << 3, ((v >> 10) & 31) << 3], axis=2).astype(np.uint8).tobytes()

    # ------------------------------------------------------------------ libpad (port shims/pad.c)
    def pad_vblank(self):
        if self.pad_script:
            m = 0
            for f, ln, count, period, mask in self.pad_script:
                d = self.frame - f
                if d >= 0 and d // period < count and d % period < ln:
                    m |= mask
            self.pad_buttons = m
        if not self.pad_started:
            return
        c = self.cpu
        if self.pad_buf[0]:
            b = ~self.pad_buttons & 0xFFFF
            c.write(self.pad_buf[0], bytes([0, 0x41, b & 0xFF, b >> 8]))
        if self.pad_buf[1]:
            c.w8(self.pad_buf[1], 0xFF)

    def h_PadInitDirect(self, c):
        self.pad_buf = [c.R[4], c.R[5]]
        for a in self.pad_buf:
            if a:
                c.w8(a, 0xFF)

    def h_PadStartCom(self, c):
        self.pad_started = True

    def h_PadStopCom(self, c):
        self.pad_started = False

    def h_PadGetState(self, c):
        c.R[2] = 6 if c.R[4] == 0 else 0

    def h_PadInfoMode(self, c):
        c.R[2] = 4 if c.R[5] == 1 else 0

    # ------------------------------------------------------------------ libcd: the port's virtual disc (shims/cd_virtual.inc)
    def cd_find(self, lba):
        for f in self.cd_files:
            if f[1] <= lba < f[1] + f[2]:
                return f
        return None

    def cd_read_sectors(self, lba, count, nbytes):
        out = bytearray()
        for i in range(count):
            f = self.cd_find(lba + i)
            if f is None:
                print("[emu] CD read of lba %d: no file there (frame %d)" % (lba + i, self.frame), file=sys.stderr)
                return None
            d = bytearray(nbytes)
            skip = 12 if nbytes > 2048 else 0
            if skip:
                d[0:4] = lba_to_loc(lba + i)
                d[3] = 2
                d[6] = d[10] = 0x08
            d[skip:skip + 2048] = self.disc.data(f[4] + lba + i - f[1])
            out += d
            if lba + i == f[1] and f[0].startswith("BIN/"):
                self.loads.append((self.frame, f[0]))
                if self.verbose:
                    print("[emu] frame %d: loading %s" % (self.frame, f[0]))
        return bytes(out)

    def h_CdSearchFile(self, c):
        fp, name = c.R[4], c.cstr(c.R[5])
        rel = name.lstrip("\\/").split(";")[0].replace("\\", "/").upper()
        f = next((f for f in self.cd_files if f[0] == rel), None)
        if f is None:
            if rel not in self.disc.files or len(self.cd_files) == 64:
                print("[emu] CdSearchFile(%r): not found (frame %d)" % (name, self.frame), file=sys.stderr)
                c.R[2] = 0
                return
            ilba, size = self.disc.files[rel]
            f = [rel, self.cd_next, (size + 2047) // 2048, size, ilba]
            self.cd_next += f[2] + 16
            self.cd_files.append(f)
            if self.verbose:
                print("[emu] CdSearchFile(%r): %d bytes, virtual lba %d (frame %d)" % (name, size, f[1], self.frame))
        c.write(fp, lba_to_loc(f[1]) + struct.pack("<I", f[3]) + rel.encode("ascii")[:16].ljust(16, b"\0"))
        c.R[2] = fp

    def h_CdMode(self, c):
        c.R[2] = self.cd_mode

    def h_CdLastCom(self, c):
        c.R[2] = self.cd_last_com

    def h_CdControl(self, c):
        com, param, result = c.R[4] & 0xFF, c.R[5], c.R[6]
        self.cd_last_com = com
        if com in (2, 0x15, 0x16) and param:
            self.cd_target, self.cd_target_pending = loc_to_lba(c.read(param, 3)), True
        if com in (0x15, 0x16):
            self.cd_pos, self.cd_target_pending, self.cd_reading = self.cd_target, False, False
        if com in (6, 0x1B):
            if param:
                self.cd_target, self.cd_target_pending = loc_to_lba(c.read(param, 3)), True
            if self.cd_target_pending:
                self.cd_pos, self.cd_target_pending = self.cd_target, False
            self.cd_reading = True
        if com in (9, 8, 0x0A):
            self.cd_reading = False
        if com == 14 and param:
            self.cd_mode = c.r8(param)
        res = bytearray(8)
        res[0] = 0x22 if self.cd_reading else 0x02
        if com == 0x10:
            res[0:4] = lba_to_loc(self.cd_pos)
            res[3] = 2
        elif com == 0x11:
            loc = lba_to_loc(self.cd_pos)
            res[0], res[1] = 1, 1
            res[2:6] = lba_to_loc(max(self.cd_pos - 150, 0))
            res[5:8] = loc[0:3]
        self.cd_result = bytes(res)
        if result:
            c.write(result, self.cd_result)
        if self.cd_sync_cb and com != 2:
            self.cpu.call(self.cd_sync_cb, 2, result)
        c.R[2] = 1

    def h_CdControlF(self, c):
        c.R[6] = 0
        self.h_CdControl(c)
    h_CdControlB = h_CdControl

    def h_CdSync(self, c):
        if c.R[5]:
            c.write(c.R[5], self.cd_result)
        c.R[2] = 2

    def h_CdReady(self, c):
        c.R[2] = 1 if self.cd_reading else 2

    def _cb(attr):
        def f(self, c):
            old = getattr(self, attr)
            setattr(self, attr, c.R[4])
            c.R[2] = old
        return f
    h_CdSyncCallback = _cb("cd_sync_cb")
    h_CdReadyCallback = _cb("cd_ready_cb")
    h_CdReadCallback = _cb("cd_read_cb")
    h_CdDataCallback = _cb("cd_data_cb")

    def h_CdGetSector(self, c):
        n = 4 * c.R[5]
        d = self.cd_sector[self.cd_sector_off:self.cd_sector_off + n]
        c.write(c.R[4], d + bytes(n - len(d)))
        self.cd_sector_off += n
        c.R[2] = 1
    h_CdGetSector2 = h_CdGetSector

    def h_CdRead(self, c):
        n, buf, mode = c.R[4], c.R[5], c.R[6]
        nbytes = 2340 if mode & 0x20 else 2048
        if self.cd_target_pending:
            self.cd_pos, self.cd_target_pending = self.cd_target, False
        d = self.cd_read_sectors(self.cd_pos, n, nbytes)
        if d is None:
            c.R[2] = 0
            return
        c.write(buf, d)
        self.cd_pos += n
        self.cd_sectors += n
        if self.cd_read_cb:
            self.cpu.call(self.cd_read_cb, 2, 0)
        c.R[2] = 1

    def h_CdReadSync(self, c):
        if c.R[5]:
            c.w8(c.R[5], 2)
        c.R[2] = 0

    def h_CdIntToPos(self, c):
        c.write(c.R[5], lba_to_loc(_cpu.s32(c.R[4])))
        c.R[2] = c.R[5]

    def h_CdPosToInt(self, c):
        c.R[2] = loc_to_lba(c.read(c.R[4], 3)) & 0xFFFFFFFF

    def cd_vblank(self):
        if self.cd_reading and not self.cd_ready_cb:       # XA streaming: the head moves 2.5 sectors per vblank
            self.cd_xa_half += 5 if self.cd_mode & 0x80 else 2
            n = self.cd_xa_half // 2
            self.cd_xa_half -= 2 * n
            self.cd_pos += n
        k = 0
        while k < 4 and self.cd_reading and self.cd_ready_cb:
            nbytes = 2340 if self.cd_mode & 0x20 else 2048
            d = self.cd_read_sectors(self.cd_pos, 1, nbytes)
            if d is None:
                self.cd_reading = False
                break
            self.cd_sector = d + bytes(2352 - len(d))
            self.cd_sector_off = 0
            self.cd_pos += 1
            self.cd_sectors += 1
            res = 0x80000E80             # 8 bytes of RAM in the unused kernel area: the {0x22} result the port passes
            self.cpu.write(res, b"\x22" + bytes(7))
            self.cpu.call(self.cd_ready_cb, 1, res)
            k += 1

    def h_StGetNext(self, c):
        c.write(FAKE_ST, struct.pack("<4H2I2H", 0, 0, 0, 0, 0x7FFFFFFF, 0, 320, 240) + bytes(64))
        c.w32(c.R[4], FAKE_ST + 0x20)
        c.w32(c.R[5], FAKE_ST)
        c.R[2] = 0

    # ------------------------------------------------------------------ libsnd / libspu: ids and allocations only
    def h_SsVabFakeHead(self, c, sbaddr=None):
        hdr, vabid = c.R[4], _cpu.s32(c.R[5]) & 0xFFFF
        vabid = vabid - 0x10000 if vabid & 0x8000 else vabid
        sb = c.R[6] if sbaddr is None else sbaddr
        r = self._vab_head(hdr, vabid, sb)
        c.R[2] = r & 0xFFFFFFFF

    def _vab_head(self, hdr, vabid, sb):
        c = self.cpu
        vabs = self.snd["vabs"]
        if c.read(hdr, 4) != b"pBAV":
            return -1
        vid = vabid
        if vid < 0 or vid >= 16:
            vid = next((i for i in range(16) if i not in vabs), 16)
        if vid >= 16:
            return -1
        ps, vs = c.r16(hdr + 0x12), c.r16(hdr + 0x16)
        if ps > 128 or vs > 254:
            return -1
        sizes = [c.r16(hdr + 0x20 + 0x800 + ps * 0x200 + 2 * k) for k in range(vs + 1)]
        tone_base, g = [], 0
        for p in range(128):
            if c.r8(hdr + 0x20 + p * 16):
                tone_base.append(16 * g)
                g += 1
            else:
                tone_base.append(-1)
        vags = []
        tones = {}
        for p in range(128):
            if tone_base[p] >= 0:
                for t in range(16):
                    tones[(p, t)] = c.r16(hdr + 0x20 + 0x800 + (tone_base[p] + t) * 32 + 0x16)
        vabs[vid] = dict(ps=ps, vs=vs, base=sb, body=sum(s * 8 for s in sizes[1:]), tone_base=tone_base, tones=tones)
        return vid

    def h_SsVabOpenHead(self, c):
        hdr, vabid = c.R[4], c.R[5] & 0xFFFF
        vabid = vabid - 0x10000 if vabid & 0x8000 else vabid
        s = self.snd
        vid = self._vab_head(hdr, vabid, s["spu_next"])
        if vid >= 0:
            n = s["vabs"][vid]["body"]
            if s["spu_next"] + n > 0x80000:
                s["spu_next"] = 0x1010
                self._vab_head(hdr, vid, s["spu_next"])
            s["spu_next"] += (n + 15) & ~15
        c.R[2] = vid & 0xFFFFFFFF

    def h_SsVabOpenHeadSticky(self, c):
        self.h_SsVabFakeHead(c)

    def h_SsVabTransBody(self, c):
        vid = c.R[5] & 0xFFFF
        c.R[2] = vid if vid in self.snd["vabs"] else 0xFFFFFFFF

    def h_SsVabTransBodyPartly(self, c):
        c.R[5] = c.R[6]
        self.h_SsVabTransBody(c)

    def h_SsVabFakeBody(self, c):
        c.R[2] = c.R[4]

    def h_SsVabClose(self, c):
        self.snd["vabs"].pop(c.R[4] & 0xFFFF, None)

    def h_SsSeqOpen(self, c):
        seqs = self.snd["seqs"]
        if c.read(c.R[4], 4) != b"pQES":
            c.R[2] = 0xFFFFFFFF
            return
        sid = next((i for i in range(8) if i not in seqs), 8)
        if sid == 8:
            c.R[2] = 0xFFFFFFFF
            return
        seqs[sid] = dict(playing=0)
        c.R[2] = sid

    def h_SsSeqPlay(self, c):
        s = self.snd["seqs"].get(c.R[4] & 0xFFFF)
        if s is not None:
            s["playing"] = 1

    def h_SsSeqStop(self, c):
        s = self.snd["seqs"].get(c.R[4] & 0xFFFF)
        if s is not None:
            s["playing"] = 0

    def h_SsSeqClose(self, c):
        self.snd["seqs"].pop(c.R[4] & 0xFFFF, None)

    def h_SsIsEos(self, c):
        s = self.snd["seqs"].get(c.R[4] & 0xFFFF)
        c.R[2] = 1 if s and s["playing"] else 0

    def h_SsSepOpen(self, c):
        c.R[2] = self.snd["sep"] & 31
        self.snd["sep"] += 1

    def h_SsUtKeyOnV(self, c):
        voice, vabid, prog = (_cpu.s32(c.R[i] << 16) >> 16 for i in (4, 5, 6))
        tone = _cpu.s32(c.R[7] << 16) >> 16
        vb = self.snd["vabs"].get(vabid)
        if not (0 <= voice < 24) or vb is None or not (0 <= prog < 128) or vb["tone_base"][prog] < 0:
            c.R[2] = 0xFFFFFFFF
            return
        vag = vb["tones"].get((prog, tone & 15), 0)
        c.R[2] = voice if 0 < vag <= vb["vs"] else 0xFFFFFFFF

    def h_SsUtKeyOffV(self, c):
        voice = _cpu.s32(c.R[4] << 16) >> 16
        c.R[2] = 0 if 0 <= voice < 24 else 0xFFFFFFFF

    def h_SsUtChangePitch(self, c):
        c.R[2] = 0

    def h_SpuGetAllKeysStatus(self, c):
        c.write(c.R[4], bytes(24))      # not modelled: every voice off (the port runs ADSR envelopes)
        c.R[2] = 0

    def h_SpuMalloc(self, c):
        a = self.snd["spu_alloc"]
        self.snd["spu_alloc"] = (a + ((c.R[4] + 15) & ~15)) & 0xFFFFFFFF
        c.R[2] = a

    def h_SpuInitMalloc(self, c):
        c.R[2] = c.R[4]

    def h_SpuSetTransferMode(self, c):
        c.R[2] = c.R[4]

    def h_SpuSetReverb(self, c):
        c.R[2] = c.R[4]

    def h_SpuReserveReverbWorkArea(self, c):
        c.R[2] = c.R[4]

    def h_SpuWrite(self, c):
        c.R[2] = min(c.R[5], 0x7EFF0)

    def h_SpuRead(self, c):
        c.R[2] = c.R[5]

    # ------------------------------------------------------------------ memory card: an empty formatted card, at once
    def _card_done(self, c=None):
        self.deliver(0xF0000011, 4)
        self.deliver(0xF4000001, 4)
        if c is not None:
            c.R[2] = 1

    h__card_info = h__card_load = h__card_clear = h__card_format = _card_done

    def h__card_read(self, c):
        c.write(c.R[6], bytes(0x80))
        self._card_done(c)

    def h__card_write(self, c):
        self._card_done(c)

    def h_firstfile(self, c):
        c.R[2] = 0
    h_firstfile2 = h_nextfile = h_firstfile

    def h_open(self, c):
        c.R[2] = 0xFFFFFFFF
    h_lseek = h_read = h_write = h_close = h_open

    def h_erase(self, c):
        c.R[2] = 0

    def h_format(self, c):
        c.R[2] = 1


class StopRun(Exception):
    pass

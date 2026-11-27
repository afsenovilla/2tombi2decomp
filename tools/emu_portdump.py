# gdb -batch -x tools/emu_portdump.py: RAM and GP0 packet dumps of build/port/tomba2 at given frames, without changing the
# port (docs/EMU.md).  tools/emu_compare.py runs it as
#   EMU_DUMP_FRAMES=100,200 EMU_DUMP_DIR=DIR EMU_PORT_LOG=DIR/port_log.txt EMU_PORT_ARGS='--frames N ...' \
#     gdb -batch -x tools/emu_portdump.py build/port/tomba2
# A breakpoint on port_gpu_vblank (where the port writes its frame dumps) reads port_frame; at a dump frame F it writes
# DIR/ram_F.bin (2 MB RAM at 0x80000000 + 1 KB scratchpad at 0x1F800000, the emulator's layout) and sets the port's own
# port_dump_packets = F, so its DrawOTag prints that frame's packets ("PK@..." lines) to its log; the log offsets at F and
# F + 1 cut DIR/packets_F.txt out of it.  The breakpoint never stops the program (Breakpoint.stop returns False).
import os
import struct

import gdb

frames = sorted({int(x) for x in os.environ.get("EMU_DUMP_FRAMES", "").split(",") if x})
want = set(frames)
out = os.environ["EMU_DUMP_DIR"]
log = os.environ["EMU_PORT_LOG"]
args = os.environ.get("EMU_PORT_ARGS", "")
marks = {}


def addr(sym):
    return int(gdb.parse_and_eval("(unsigned int)&%s" % sym))


class VblankBP(gdb.Breakpoint):
    def stop(self):
        inf = gdb.selected_inferior()
        f = struct.unpack("<i", bytes(inf.read_memory(self.frame_addr, 4)))[0]
        size = os.path.getsize(log) if os.path.exists(log) else 0
        if f - 1 in want:
            marks[f - 1] = (marks[f - 1][0], size)
            inf.write_memory(self.pk_addr, struct.pack("<i", 0))
        if f in want:
            ram = bytes(inf.read_memory(0x80000000, 0x200000))
            try:
                sp = bytes(inf.read_memory(0x1F800000, 0x400))
            except gdb.MemoryError:
                sp = bytes(0x400)
            with open(os.path.join(out, "ram_%06d.bin" % f), "wb") as fh:
                fh.write(ram + sp)
            inf.write_memory(self.pk_addr, struct.pack("<i", f))
            marks[f] = (size, None)
        return False


gdb.execute("set pagination off")
gdb.execute("set confirm off")
gdb.execute("handle SIGSEGV nostop noprint pass")
gdb.execute("handle SIGALRM nostop noprint pass")
bp = VblankBP("port_gpu_vblank", internal=True)
bp.silent = True
gdb.execute("starti %s > %s 2>&1" % (args, log))
bp.frame_addr = addr("port_frame")
bp.pk_addr = addr("port_dump_packets")
gdb.execute("continue")
size = os.path.getsize(log)
text = open(log, "rb").read()
for f, (a, b) in marks.items():
    seg = text[a:b if b is not None else size].decode("latin-1").splitlines()
    with open(os.path.join(out, "packets_%06d.txt" % f), "w") as fh:
        fh.write("".join(l + "\n" for l in seg if l.startswith("PK@")))

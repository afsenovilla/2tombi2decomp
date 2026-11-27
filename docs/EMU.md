# Reference emulator (tools/psxemu) and the port comparison

A PlayStation in Python that runs Tomba! 2 USA's own MIPS code (MAIN.EXE, the overlays and the "pure" Psy-Q libraries)
from the player's disc image, with the native port's command line and dump layout. `tools/emu_compare.py` runs it and
`build/port/tomba2` on the same input and diffs them frame by frame: it names the first frame where the port's picture,
VRAM, GP0 packets or RAM leave the retail code's, which is where a shim or a native function is wrong.

It is Tombi-Decomp's `tools/psxemu` (MIT, same author: `cpu.py` block-compiling R3000A, `gte.py`, `gpu.py` software
rasterizer copied; `machine.py` adapted; `tools/test_psxemu.py`), credited in THIRD_PARTY_NOTICES.md and the file
headers. Nothing of the game is in the repo: `tools/psxemu/syms/main_usa.csv` holds library names and addresses only.

## Commands

```
python3 -I tools/emu_run.py --frames 3000 --dump-frames DIR --dump-every 100 [--dump-vram] [--ram-at F,...]
    [--dump-ram] [--dump-packets all|F,...] [--pad-script 400:start,600:cross,...] [--disc game/usa.img]
    [--save-state FILE] [--load-state FILE] [--port-math ratan2,SquareRoot0] [-v]
python3 -I tools/emu_compare.py --route title|attract|a00 [--out DIR] [--ram-at F,...] [--packets-at F,...]
python3 -I tools/emu_compare.py --frames N --every K [--pad-script S] [--at F,...] [--skip-port | --skip-emu]
    [--port-args=--keys-off]     # extra port options: --keys-off = SpuGetAllKeysStatus all off, as the emulator
    [--emu-args="--demo-takeover 2550"]   # extra emulator options
python3 -I tools/emu_run.py ... --demo-takeover F   # from vblank F the attract demo's input replay plays the pad
                                                    # script (the port's --demo-takeover, docs/PORT.md §0.4)
python3 -I tools/test_psxemu.py                      # unit tests (no game data)
python3 -I tools/psxemu/t2syms.py                    # rebuild syms/main_usa.csv from build/main.elf + asm/main
```

- Dumps (both programs, frame = vblank count = the port's `port_frame`, taken after the vblank's callbacks):
  `frame_NNNNNN.png` (the displayed DISPENV area), `vram_NNNNNN.png` (1024x512, 5-bit channels << 3: the port's
  `--dump-vram`), `ram_NNNNNN.bin` (**the RAM dump layout**: 2 MB of RAM from 0x80000000, then the 1 KB scratchpad
  from 0x1F800000; 0x200400 bytes), `packets_NNNNNN.txt` (every GP0 packet DrawOTag / DrawPrim sent while
  `port_frame == NNNNNN`, one `PK@<KSEG0 address> <words>` line each: the port's own `port_dump_packets` format).
- The port has no `--dump-ram` and no `--dump-packets` option: `tools/emu_portdump.py` (a gdb Python script) takes
  both from the unchanged binary: a breakpoint on `port_gpu_vblank` that never stops reads `port_frame`, dumps
  RAM + scratchpad at the asked frames and sets the port's `port_dump_packets` variable so its DrawOTag prints the
  packets. If the port adds the options, they should use these layouts.
- `emu_compare.py` writes `OUT/port`, `OUT/emu`, `OUT/diff/frame_N.png` (port | emulator | differing pixels in red)
  and `OUT/report.txt`: per frame the differing pixels with their regions, the differing VRAM regions, the first
  differing packet (both decoded), the differing RAM ranges named from build/main.elf (`kernel`, `stack` (from
  0x801E0000), `overlay 0x80108F9C` / `0x80188000`, the scratchpad), and the BIN/ loads of both runs (a load at
  another frame means the timing no longer agrees). Default OUT: `build/emu_compare/<route>`.
- Routes: `title` (400 frames, every 25), `attract` (6000, every 100, no input: title, the demo in A00, back to the
  title, the demo in A01), `a00` (the 10600-frame play script of docs/PORT.md §0: New Game, story text, A00 opening,
  journal tutorial, free play).
- Speed (this container, CPython 3.13): about 5 M MIPS instructions/s: the title at 30-40 frames/s, loading screens
  100+, gameplay 5-8 frames/s; the attract route takes about 15 minutes, a00 about 30. pypy3 7.3.15 (with numpy
  1.26 in a venv) was **10x slower** (0.5 M instructions/s): every basic block is Python source compiled with
  `exec`, which pypy's JIT does not warm up on. `--save-state` / `--load-state` (pickled RAM, VRAM, CPU and HLE
  state at a vblank) skip the boot when bisecting a late frame: e.g. save at 1200, then dump every frame from there.

## What the emulator emulates (machine.py)

The HLE boundary is the port's (port/shims), with the port's semantics, so that a difference comes from the port's
native code or its shim *implementations*, not from a different timing model:

- **Retail MIPS code**: all of MAIN and the overlays, and the pure libraries (libc, libc2, libgte, libsn and libgpu's
  primitive helpers: t2syms.py's `pure` column, the port's gen_t2.py PURE_LIBS / PURE_GPU), **even where the port
  replaces them by C** (rsin, rcos, ratan2, SquareRoot0, RotMatrix*, MulMatrix0, ApplyMatrix*, RotTransPers,
  SetDrawMode, SetDrawArea, memcpy, rand ...): their retail behaviour is the reference.
- **HLE like the port**: libgpu (LoadImage, StoreImage, MoveImage, ClearImage, PutDrawEnv / GetDrawEnv, PutDispEnv,
  ClearOTag(R), DrawOTag (24-bit links, a 0x80 in the tag's length byte ignored), DrawPrim, GPU_cw, SetDispMask),
  libetc (VSync, VSyncCallback(s)), libapi (OpenEvent / TestEvent / DeliverEvent, threads OpenTh / ChangeTh / CloseTh
  on the game's own stacks), libcd (the port's virtual disc: CdSearchFile gives each file a position from LBA 1000
  in lookup order, 16 sectors apart; CdRead at once; ReadN / ReadS + CdReadyCallback deliver 4 sectors per vblank
  as 2340-byte sectors with a made-up header; the XA head moves 2.5 sectors per vblank; CdlGetlocL / P), libpad
  (PadInitDirect buffers filled each vblank after PadStartCom; the `--pad-script` syntax of shims/pad.c), libsnd /
  libspu (only what the game reads back: VAB / SEQ ids, SPU allocations, SsUtKeyOnV's voice or -1, SsIsEos),
  libcard (an empty card, every operation completes at once with its events), libpress / streaming (StGetNext
  reports a frame past the end: movies end at once). Every other hardware-library function returns 0 (the port's
  logged stubs).
- **Timing**: a vblank on VSync(0 / n) and when a loop spins on memory (a backward branch of at most 32 bytes over
  loads whose base registers the loop does not write, no stores, calls or jumps: the port's mips_interp.c
  `is_spin`). The vblank: frame + 1, pad, virtual disc, the four VSyncCallbacks, the VBlank event handler, the
  VSyncCallback, then the dumps (port psyq.c `port_vblank`). Both programs load BIN/START.BIN at frame 8,
  DEMO.BIN 122, SOP.BIN 130, A00.BIN 1065 in attract mode (checked).
- **GPU**: T1's numpy rasterizer with the top-left fill rule (T1 drew the bottom row of every polygon: the title's
  "NewGame" / "LoadGame" labels differed by 25 pixels until this was fixed); textures sampled by truncation, the
  port rounds to nearest (the same for unit gradients). Not emulated: dithering, the mask bit check.
- Not emulated: sound output (and so SpuGetAllKeysStatus reports every voice off, the port runs ADSR envelopes),
  MDEC, memory card contents, the boot executable (SCUS_944.54: MAIN.EXE is started directly, as the port does).

## Port vs emulator: findings (2026-11-28)

See STATUS "2026-11-28 (3): reference emulator" for the run of the day. Method for the next difference: run a route,
take the first frame that differs, dump RAM at every frame before it from a saved state (`emu_run.py --load-state
--ram-at` and `emu_compare.py --ram-at`), find the first differing byte, then watch it: in the emulator a store hook
(`cpu.set_store_hook`, `tools/psxemu/cpu.py`), in the port a gdb hardware watchpoint (`watch *(unsigned char *)ADDR`
with `printf` of `port_frame`, `$pc` and `port_mips_cur_pc`). The pc that writes a different value names the
function; its inputs name the shim.

1. **ratan2 (port/shims/psyq.c) is not the retail one** (attract demo 1, frame 1216 -> 1219 -> everything after):
   f_RebuildCameraViewTransform stores `ratan2(...)` at 0x1F8000F0: 118 in the retail code, 117 in the port
   (0x8006D150). The camera angle is off by one unit, and from frame 1219 the actors' positions and counters
   (0x800F1122 = 0x14 vs 0x15, ...) and the picture differ (frame 1300: the demo's Tomba and HUD in other places).
   Checked directly: retail ratan2 against the shim's binary search over 3000 random (y, x) pairs: **1329 differ**
   by one (e.g. ratan2(-12273, 12468) = -507 retail, -506 port). Fix for the port: drop the ratan2 shim and run
   src/main/psyq/libgte/ratan2.c (matched C) or the retail code.
2. **SquareRoot0 (same file) is exact, the retail one is not**: retail SquareRoot0 is Sony's table + GTE
   leading-zero approximation (SquareRoot0(10000) = 99, (1000000) = 999, (245952131) = 15664), the shim returns
   the exact integer square root (100, 1000, 15682): 2971 of 3000 random values differ. Fix: drop the shim (the
   retail function is asm by design: interpreted).
3. **RotMatrix (same file) rounds differently**: 296 of 300 random angle triples give a matrix with one or more
   elements off by 1-2 (e.g. RotMatrix(-3170, -2596, -2706): retail m[1][0] = -1088, port -1089; m[2][1] -1770 vs
   -1772). With ratan2 and SquareRoot0 replaced by the port's versions in the emulator (`--port-math`), the A00
   story-text scene (frame 800) still differs: the game state is equal, only the primitive buffer (vertex
   positions) and three scratchpad words (0x1F800080, 0x1F8000C0 / C2: a matrix) differ, which is what a rotation
   matrix off by one unit does. Fix: drop the RotMatrix shim (src/main/psyq/libgte/RotMatrix.c is matched C).
4. **RotTransPers**: 1 of 300 random cases gives a screen y off by one (the GTE divide: port/runtime/gte.c against
   T1's gte.py, one of the two is not the hardware's UNR divide); rare, not seen in a frame yet.
5. Equal: rsin / rcos (all 4096 angles; the shim's Taylor table is exact), RotMatrixX / Y / Z, MulMatrix0,
   ApplyMatrix, ApplyMatrixSV (300 random inputs each). `python3 -I tools/emu_shimcheck.py` repeats all of this:
   it builds port/shims/psyq.c + port/runtime/gte.c as a host shared library (build/emu_shim/, the port's other
   symbols stubbed) and calls each shim through ctypes next to the retail function in the emulator.
6. Title (frames 0-400): pixel-identical, VRAM identical, the 7 GP0 packets identical; RAM differs only in the
   kernel area, the stacks (the port's threads run on native stacks), libgpu / libapi statics the HLE'd functions
   never set (0x800A6300, 0x80102430, 0x80105EE8), and the primitive buffer's tag bytes (0x80 in the length byte
   where an interpreted link store wrote a KSEG0 link: port mips_interp.c `kcell`).
7. Attract mode up to frame 1216 (the A00 load included) and the A00 route up to the story text (frame 700): the
   same frames and GP0 packets. Every BIN/ load at the same frame as the port over the whole 6000-frame attract
   route (8 START, 122 DEMO, 130 SOP, 1065 A00, 3021 SOP, 3956 A01, 5890 SOP; 546 s, 11 frames/s) and on the A00
   route (607 GAME.BIN, 1473 A00.BIN, 1621 OPN.BIN): the timing model holds even after the pictures diverge.

What the emulator does not show yet: whether the port's GPU rasterizer and the emulator's agree on 3D scenes (every
3D frame so far already differs in its geometry because of 1 and 3); once the port takes the retail ratan2 /
SquareRoot0 / RotMatrix, `emu_compare.py --route attract` and `--route a00` will show the next difference.

## The A00 net climb (2026-11-28, docs/PORT.md §0.4)

Attract demo 1 walks Tomba to the net beside the tower; `--demo-takeover 2550` on both sides hands him to the pad
script there (`2560:right:40,2600:right+cross:15,2615:right:30,2650:up:400`: onto the net, then up). Run with
`emu_compare.py --frames 2760 --every 50 --port-args="--keys-off --demo-takeover 2550" --emu-args="--demo-takeover 2550"
--ram-at 1300,...,2750` (275 s for the emulator): with the port's stage-5 fix both climb the same way; the player actor
is byte-equal at every dump, and the rest of the RAM differs only where it is known to (OT link high bytes, the
libgpu statics, the emulator's zero DR_AREA words). Before the fix the port's Tomba stayed on the net.

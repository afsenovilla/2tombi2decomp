# Native port (PC first)

The port compiles the matched C of `src/` for the host and runs it against the player's own game files. It is built
the way the first game's project built its port (Tombi-Decomp, same author, MIT: `port/` and `port2/`, documented in
its `docs/PORT.md`); the code that is copied from there says so at the top of each file, and THIRD_PARTY_NOTICES.md
credits it. Nothing of the game is in the repo: the port reads `game/usa/` (the extracted USA disc) at run time.

The matching build stays authoritative: the port only **reads** `src/`, `build/<prog>.elf` and `asm/<prog>/`, and
`python3 tools/build.py` gives 29 / 29 OK with or without it.

## 1. Status: stage 1, milestone P0 (2026-11-27)

```
python3 tools/build.py main                    # once (or the full build): the port reads build/main.elf and asm/main/
cmake -S port -B build/port -G Ninja && cmake --build build/port
build/port/tomba2 --frames 6000 --dump-frames DIR --dump-every 100            # attract mode (no input)
build/port/tomba2 --frames 9600 --dump-frames DIR --dump-every 200 \
    --pad-script 400:start,600:cross,800:cross,1000:cross,1200:cross,1400:start,6000:circle:10x15/60
#   New Game -> story text (skipped with Start) -> A00 opening cutscene -> dialogue advanced with Circle
#   options: --exe PATH (default game/usa/MAIN.EXE)  --data DIR (default game/usa: the extracted disc files)
#            --frames N  --dump-frames DIR  --dump-every N  --dump-vram  --realtime [--hz 50|60]
#            --pad-script FRAME:BUTTONS[:LEN[xCOUNT/PERIOD]],...  --autostart N
#            --trace-cd  --no-interp  --interp ADDR (force a function into the interpreter when called from
#            interpreted code or a thunk)  --trace-interp  --entry ADDR  -v [-v]
```

Headless, a 9600-frame run takes about a minute (most of it in the interpreter). Measured on the USA files:

| frame | what runs |
|---|---|
| 0 | crt0 (`__SN_ENTRY_POINT`, interpreted) clears the BSS, `InitHeap` (shim), `main` = `func_80050B08` (asm: interpreted) |
| 3 | init: `SsInit` and the SPU set-up (silent), `InitCARD` / `_bu_init` (stubs), `PadInitDirect`, `VSyncCallback(func_800506B4)`; `CdSearchFile("\BIN\START.BIN")` |
| 8-15 | `BIN/START.BIN` read through the game's own data-ready reader (`func_8001D7C4`: `CdReadyCallback` + `CdGetSector`, 2340-byte sectors whose header position the game checks); every file of the disc looked up (START.BIN's list) |
| 122, 130 | `BIN/DEMO.BIN` (0x80106228) and `BIN/SOP.BIN` (0x80108F9C) loaded; `MOVIE/OP.STR` opened at 155 (the opening movie, skipped: §4) |
| ~200 | **the title screen** (logo, characters, "New Game / Load Game", copyright) |
| no input: ~1300-3000 | **attract demo 1** in the Tomba village (3D scene, HUD, Tomba jumping) |
| ~3100-3900, 4200-5600 | back to the title, then **attract demo 2** (a mine / fire area); crash at 5637 (§5) |
| Start, Cross | New Game: `BIN/GAME.BIN` loaded at 607, the **story text** ("Tomba is living peacefully...") |
| Start at 1400 | text skipped: `BIN/A00.BIN` at 1473, `BIN/OPN.BIN` (the opening event) at 1621, XA voice clips started (`VOICE.XA`, ReadS) |
| 1750-6000 | **the A00 opening cutscene** in engine with its dialogue boxes ("Tomba! Look!! That house is on fire!") |
| Circle from 6000 | dialogue advances: **the Adventure Journal tutorial box** (frame 8400-8800); 9600 frames without a crash |

Frame dumps of a run are PNGs (320x240, the displayed DISPENV area) in the `--dump-frames` directory. Per 100
frames the log prints the CD sectors read, the ordering tables drawn and the calls that ran in the MIPS interpreter;
each overlay load is logged (`frame N: loading BIN/A00.BIN`); at the end, every stubbed Psy-Q function that was
called. A watchdog (SIGALRM, every 2 s) reports where a run stands when the frame counter stops (native EIP, the
interpreter's pc, the last call thunk) and stops it after 20 s.

## 2. Architecture (the fixed-address model of T1's `port/`)

```
src/<prog>/*.c ──gen_t2.py sources (host cpp, split, filter)──> build/port/gen/src ──gcc -m32──┐
port/shims (Psy-Q API on the host) ─────────────────────────────────────────────────────────────┤
port/runtime (memory, MIPS interpreter, GTE, threads, loader) ─────────────────────────────────┤──> tomba2
gen_t2.py link: syms.ld (retail data -> address), thunks.S, funcmap.c ─────────────────────────┘
game/usa/MAIN.EXE ──loaded at 0x80010000──> PS1 RAM mapped at 0x80000000 in the process
game/usa/** (the extracted disc) ──virtual disc──> CdSearchFile / CdRead / CdGetSector
```

T1 had two ports. `port/` (its prototype) mapped the PS1 RAM at its own address in an i386 process and ran code it
had no C for in a small MIPS interpreter; `port2/` (its mature port) dropped both, because T1's decomp was complete,
and compiles everything with native pointers. **Tomba! 2 is 60 % C, so stage 1 follows T1's `port/`**: native code
and interpreted retail code must share one address space, which only the fixed-address model gives. The shims,
the GTE, the frame dumps and the generator ideas are the same in both T1 ports; `port2/`'s pieces (its GTE, its
software SPU, its MDEC, its SDL window) are taken over one by one as they are needed.

- **RAM** is one 2 MB memfd mapped at 0x80000000 (KSEG0), 0xA0000000 (KSEG1) and 0x00010000 (KUSEG mirror, for the
  game's `& 0xFFFFFF` pointers); the scratchpad and the I/O page at 0x1F800000 are plain memory (GPUSTAT preset to
  "ready"). `MAIN.EXE` is loaded at its address, so every retail datum is where the C expects it: the C's
  `D_800xxxxx` externs are linked to their retail addresses (`gen/syms.ld`), and native code and retail code share
  the one copy.
- **One native function per retail function with C.** `gen_t2.py sources` preprocesses `src/main/main.c` with the
  host cpp (`INCLUDE_ASM` empty), splits it into top-level items and writes it back filtered. A function the host
  cannot compile is left out and stays retail code: functions with MIPS inline asm (the GTE macros, 33 in MAIN),
  `static` asm helpers and their callers, and whatever the host compiler rejects (21: found by compiling, mapped
  back to the item by line). A definition whose earlier declarations conflict with it (13: gcc 2.8 accepted
  `int f();` then `u8 *f(...)`) is compiled as `NAME__def` with `NAME` an assembler alias, and the conflicting
  prototypes are removed. K&R definitions are recognised. MAIN: **892 native functions** with a retail address (of 1169 game functions; 228 are still asm).
- **Register-carried arguments** (T1 §2.1): a call that passes fewer arguments than the callee reads relied on
  `$a0-$a3` still holding a value (`func_8005A910` calls `func_8005A970()` with its own `arg0` in `$a0`;
  `((s32 (*)())f_TryStartTombaSupportInteraction)()` in `func_80057C08`; `ApplyMatrixSV(arg0 + 0x18)` with the
  caller's `a1` / `a2`). `gen_t2.py` takes each callee's arity from its asm (every function of the program, Psy-Q
  included: 1 + the highest `$a` register read before written) or its C definition, and appends
  `PORT_ARG(i)` (the caller's own incoming argument i, read through the frame pointer) to the short calls: 28 in
  MAIN (`gen/forwarded_main.txt`). The first two attract-demo crashes were these.
- **Calls to code without C** go through a thunk per name (`gen/thunks.S`: `push name; push addr; call
  port_resolve_call; jmp *eax`): the native function if one exists, a shim, the MIPS interpreter at that address,
  or a logged stub. A call to a retail address from native code (a function pointer read from retail data) faults
  (RAM is not executable) and the SIGSEGV handler redirects it the same way (T1's trampoline).
- **The MIPS interpreter** (`runtime/mips_interp.c`, T1's) runs the retail code where it lies in RAM: the asm-only
  MAIN functions and **all overlay code** (OPN, DEMO, GAME, A00..A0L: no overlay C is compiled in stage 1; the game
  loads them itself, so their bytes are in RAM). A `jal`/`jalr` to an address with native code calls it with
  `$a0-$a3` + four stack words (cdecl) and takes `$v0` from `eax`. Changes for T2: a plain `j` / `jr` into native
  code is a tail call; RAM is mirrored four times in the first 8 MB (an access at 0x80200000 reads 0x80000000);
  stack arguments are read only where RAM is mapped (the crt0 stack starts 8 bytes below the end of RAM); a jump
  out of RAM code is fatal with the jump's origin.
- **Busy-waits are vblanks.** `main()` paces frames with `while (D_800E809C < wanted) ;`, the counter being bumped
  by the VSync callback. T1 had main() in C and called `port_vblank()` in that loop; here main() is interpreted, so
  the interpreter recognises a busy-wait: a short backward loop (at most 8 instructions) that loads memory through
  base registers it does not change and has no store and no call. Each pass is one emulated vblank (`port_vblank`:
  pad, CD data-ready delivery, VSync callbacks and events, frame dump).
- **Psy-Q** (`gen/funcmap.c`, from the `asm/main/*/psyq/<lib>/` tree): 582 library functions. 182 have a shim
  (`port/shims`, by name): they are called natively also from interpreted code. Without a shim, the pure libraries
  (libc, libc2, libgte, libsn and the libgpu primitive setters: 35) are interpreted; the rest touch hardware and
  are logged stubs returning 0.
- **Threads** (`OpenTh` / `ChangeTh`) are coroutines on native stacks (T1's); a thread whose entry has no C runs it in
  the interpreter.

## 3. What was copied from Tombi-Decomp and what changed

| File | From T1 | Changes for T2 |
|---|---|---|
| `runtime/sys_linux_i386.c` | `port/runtime` | one lookup table (game C, then shims), the Psy-Q address policy, stub names from the library table, the SIGALRM watchdog |
| `runtime/sys_common.c` | `port/runtime` | the symbol table for fault reports without T1's overlay tables |
| `runtime/mips_interp.c` | `port/runtime` | tail calls into native code, RAM mirrors, safe stack arguments, busy-wait detection, jump check |
| `runtime/threads.c` | `port/runtime` | interpreted thread entries, 16 threads, 4 MB stacks (each native -> interpreter transition takes 16 KB) |
| `runtime/gte.c` | `port2/runtime` | DPCS, DPCT, INTPL, DCPL, GPF, GPL, SQR, OP added (from psx-spx), the 3DS stereo hook removed |
| `runtime/main_port.c` | rewritten (T1 had main() in C) | loads MAIN.EXE, starts the crt0 in the interpreter, command line |
| `shims/gpu.c` | `port/shims` (T1's own software GPU, written from psx-spx) | Psy-Q 4.4 names (`LoadImage2`, `DrawOTag2`, `MoveImage2`, `StoreImage2`, `GPU_cw`, ...) |
| `shims/psyq.c` | `port/shims` | cut to libapi / libetc / libgte; events and root counters; four VSync callbacks |
| `shims/cd_virtual.inc` | new (replaces T1's disc-image reader) | the virtual disc over the extracted files (§4) |
| `shims/pad.c`, `shims/libc.c` | `port/shims` | `memset` left to the game's own |
| `shims/sound_stub.c` | new | silent libsnd / libspu with the return values the game waits for |
| `tools/gen_t2.py` | rewritten after `port/tools/gen_port.py` | host-cpp + item split instead of T1's line filter (§2); no GTE macro translation yet (those functions are interpreted) |

## 4. Memory map and files

| What | Where |
|---|---|
| boot exe `SCUS_944.54` | 0x80010000, entry 0x80018B6C; loads `MAIN.EXE` on the console. The port loads `MAIN.EXE` directly (the boot exe's own work, the legal screen, is skipped) |
| `MAIN.EXE` | 0x80010000-0x800BE800, entry `__SN_ENTRY_POINT` 0x800896E0 (crt0: BSS 0x800BE0D8-0x80106228, stack from `D_800A3F88`), main = `func_80050B08` |
| `GAME.BIN`, `DEMO.BIN` | 0x80106228 |
| `A00..A0L.BIN`, `SOP.BIN` | 0x80108F9C |
| `OPN.BIN`, `CRD.BIN` | 0x8018A000 |
| disc files | `BIN/START.BIN` lists the files the game looks up with `CdSearchFile`; data comes from `CD/TOMBA2.IDX/DAT/IMG/SND`, music and voices from the XA files |

**The virtual disc** (`shims/cd_virtual.inc`): `CdSearchFile` opens `game/usa/<path>` and gives the file a range of
2048-byte sectors on a made-up disc (from lba 1000, in lookup order, 16 sectors apart); `Setloc` anywhere in a range
reads that file. `CdRead` copies at once; `ReadN` / `ReadS` deliver 4 sectors per vblank to the ready callback,
with a real sector header (BCD position, mode 2, form-1 subheader) in 2340-byte mode. `GetlocL` / `GetlocP` return
the head position (also through `CdSync`'s result, where `func_8001CE04` reads it): the XA voice player
(`func_8001CFC8`) waits until the head is inside the clip; while `ReadS` streams with no ready callback the head
moves 3 sectors per vblank (the audio itself is not played yet). Movies: `StGetNext` returns a sector header whose
frame number is past the end (T1's trick), so DEMO.BIN's player (`func_801075F8`: `frameCount >= limit`) ends the
movie at once.

## 5. Open points (stage 2: free gameplay in A00, then the title screen natively)

1. **The crash at frame 5637** in attract demo 2: an interpreted overlay function (`func_80132DC0`) reads through a
   bad pointer after native `f_BuildActorModelPartPrimitives` / `func_8008007C` / `func_8007FDB0`. Same hunt as the
   first two: `--trace-interp` for the arguments, gdb on the native caller (`handle SIGSEGV nostop noprint pass`;
   the binary has symbols and frame pointers), then a missing forwarded argument, a narrow return value or a
   conflicting prototype (the 13 renamed definitions: callers see `int f()`). Also the reverse case is unhandled:
   a `void` C function whose asm caller uses `$v0` (`func_8001CE90` returns `func_8001CE04`'s value by tail call; it
   worked here because the native epilogue keeps `eax`).
2. **Input to free gameplay in A00**: the tutorial dialogues need their buttons (Triangle for the journal); a
   longer `--pad-script`, then walking (T1's M1 script is the model).
3. **GTE inline asm** to C (T1's `translate_gte_define`) so the 33 + 21 MAIN functions left to the interpreter become
   native; then the overlays' C (OPN / SOP / GAME / DEMO first, A00 next) with per-overlay renames and dispatch on the
   resident overlay (T1 §2.2; the area overlays and SOP share 0x80108F9C, GAME / DEMO 0x80106228, OPN / CRD
   0x8018A000). The overlay loads are already logged by file.
4. **Sound** (T1 `port2/shims/sound.c`: software SPU, libsnd kept as compiled code; then XA through the virtual
   disc), **memory card** (`port2/shims/card.c`), **movies** (`port2/shims/mdec.c` + the `St*` ring), the **SDL2
   window** (`port2/runtime/sdl.c`), real-time pacing at 60 Hz (USA).
5. The boot exe (`SCUS_944.54`: legal screen, then it loads MAIN.EXE) is skipped; running it first would need its
   own symbol table in the port (it is a separate program with its own copy of the library).

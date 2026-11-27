# Native port (PC first)

The port compiles the matched C of `src/` for the host and runs it against the player's own game files. It is built
the way the first game's project built its port (Tombi-Decomp, same author, MIT: `port/` and `port2/`, documented in
its `docs/PORT.md`); the code that is copied from there says so at the top of each file, and THIRD_PARTY_NOTICES.md
credits it. Nothing of the game is in the repo: the port reads `game/usa/` (the extracted USA disc) at run time.

The matching build stays authoritative: the port only **reads** `src/`, `build/<prog>.elf` and `asm/<prog>/`, and
`python3 tools/build.py` gives 29 / 29 OK with or without it.

## 0. Stage 2 (2026-11-27): playable A00 in a window

```
cmake -S port -B build/port -G Ninja && cmake --build build/port     # also builds tomba2-view when SDL2 is found
build/port/tomba2 --window                                           # SDL2 window, keyboard / controller, 60 Hz
#   keys (tomba2-view): arrows = d-pad, X = Cross, Z = Square, S = Triangle, D = Circle, Q / W = L1 / R1,
#   A / E = L2 / R2, Return = Start, Backspace = Select, F = 2x / 3x, F11 = fullscreen, Escape = quit
#   --viewer PATH, --viewer-arg ARG (repeatable: --scale N, --fullscreen, --keys up=Up,cross=X,..., --stats,
#   --dump DIR[:N]); --headless (the default) keeps the stage-1 behaviour; --save-dir DIR (memory cards);
#   --disc game/usa.img (XA music / voices from the raw image); --dump-audio FILE.wav
# free play in A00, headless (frame dumps of Tomba walking, jumping on a barrel, the "look inside" hint):
build/port/tomba2 --frames 10600 --dump-frames DIR --dump-every 50 --pad-script \
  400:start,600:cross,800:cross,1000:cross,1200:cross,1400:start,6000:circle:10x50/60,9200:right:300,\
9550:cross:10,9600:right+cross:20,9700:left:300,10050:cross:10,10100:square:10,10200:up:100,10350:down:100
```

What stage 2 changed (each item with its headless check):

- **The attract-demo-2 crash (frame 5637) is fixed**: MAIN's C `func_800633B0(a)` dispatches to the resident area
  overlay (`func_8010ACB8(a)` in A01, ...) and those read `$a1`, the second argument func_800633B0's own callers
  passed (`((s32 (*)(u8 *, s32))func_800633B0)(a, 0)`). gen_t2.py took arities only from MAIN's asm, so the call
  was not forwarded and A01 read garbage, spawned an actor on a non-model bank and crashed 1600 frames later.
  Arities now also come from every other program's asm (the highest of all copies of a name): 46 calls forwarded
  (was 28). Attract mode runs 20000 frames without a crash.
- **Narrow results** (`u8` / `s8` / `u16` / `s16`) of native functions are extended for MIPS callers
  (`PortFunc.ret`, gen_t2.py `ret_kind`): the i386 ABI leaves eax's upper bits undefined, R3000 code expects the
  extended value in `$v0`.
- **How the crash was found** (the method for the next ones): `--interp-range all` runs every MAIN function in the
  interpreter (the retail code is the reference run): no crash; then bisect `--interp-range LO-HI` on the upper
  bound with a fixed low bound (a range only takes effect for calls from interpreted code or thunks, so a native
  caller hides a buggy native callee: bisect `[LO, hi)` for the smallest hi that runs clean, which names the
  caller), then gdb watchpoints on the bad datum (`watch *(int*)ADDR if *(int*)ADDR == VALUE`; `port_mips_cur_pc`
  says which interpreted instruction wrote it) and `--watch-pc ADDR` (the interpreter's registers each time it
  reaches ADDR).
- **SDL2 window** (`--window`): T1's viewer process (`port/tools/view/tomba2_view.c`, a 64-bit SDL2 program fed
  through pipes by `runtime/window.c`; the game binary stays i386 and freestanding), 320x240 frames, 60 Hz pacing
  (`port_hz` defaults to 60: USA/NTSC). Checked with `SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy` and the
  viewer's own `--dump DIR:N` (the title screen arrives at 58-60 frames/s, none skipped).
- **The overlays' C is native** (all 27: OPN, GAME, DEMO, SOP, CRD, A00..A0L; 3416 functions, 4308 native in all
  with MAIN's 892). gen_t2.py compiles `src/<ovl>/*.c` with every name the overlay's ELF defines in the overlay
  region renamed `<ovl>_NAME` (a `-include`d header of `#define`s: the overlays share load addresses and names);
  the link step resolves prefixed names by address in that overlay's ELF. `funcmap` entries carry the overlay and
  the function's first two code words (from `build/<ovl>.bin`); the virtual disc marks an overlay resident when
  sector 0 of `BIN/<OVL>.BIN` is read, and `port_lookup` takes an overlay's native function only while that
  overlay is the resident one at its load address and its first words are in RAM, else the interpreter runs the
  bytes (`--no-ovl-native`: always the interpreter; `--ovl-interp NAME`: one overlay interpreted).
  **Check: pixel-identical frame dumps** with native and interpreted overlays: the A00 play script (212 frames)
  and 20000 frames of attract mode (80 frames: demos in A00, A01, A03).
- Generator fixes the overlays needed (each found by a frame diff against `--no-ovl-native`):
  - **a game function named as a value is its retail address** (`((void *)0x8010B37Cu)`): the A03 trolley HUD
    compares an actor's update pointer with `f_UpdatePlayerTrolleyActor`, which the spawn data set to the retail
    address; a call through such a pointer reaches the native code by the SIGSEGV trampoline, and the shims
    (threads, VSync / CD callbacks) already take retail addresses. `((T (*)())f)(...)` stays a direct call.
  - arities of MAIN functions under an overlay's own name for them (`func_80076D68` =
    `f_AdvanceActorSkeletalAnimation`), by address;
  - a call through a function pointer with an empty argument list gets the caller's arguments
    (`func_800412CC`: `a->fn()` with `a` still in `$a0`; this also fixed the story-text scene, black in stage 1);
  - block-scope prototypes are not calls; a dropped `static` helper takes its callers with it; every error line of
    a renamed definition counts as fixed by the rename (A08 lost 19 functions to the old rule).

- **The GTE inline asm is translated** (T1's `translate_gte_define`, applied to the cpp-expanded `__asm__`
  statements: `lhu $12, 0(%0)`, `mtc2`, `lwc2` / `swc2`, `.word` GTE commands, `ctc2` / `cfc2`, a scratch register
  file per function; empty `__asm__ volatile("")` barriers dropped): MAIN's 33 inline-asm functions and the
  overlays' 177 but 16 are native (4485 native functions). Frame dumps unchanged (both checks above).
  `port_prelude.h` declares the GTE entry points.

- **Memory card** (`shims/card.c`, T1 `port/shims/card.c`): two 128 KB raw card images (`tomba2_mc0.mcd`,
  `tomba2_mc1.mcd`, the common emulator layout) in `--save-dir DIR` (default: the `--data` directory, game/usa),
  written through on every change; the low-level `_card_*` calls complete at once and raise the card events
  (OpenEvent / TestEvent / DeliverEvent moved there from psyq.c), the BIOS file calls (`open` / `read` / `write`
  / `lseek` / `close` / `erase` / `format` / `firstfile` / `nextfile` on `bu00:` / `bu10:`) work on the image.
  Checked: Title -> Load Game loads CRD.BIN, formats new cards, and shows "No data for Tomba!2"; saving needs a
  save point (not scripted yet).
- **CD seeks**: Setloc only sets the target; SeekL / SeekP and the next ReadN / ReadS / CdRead go there. The XA
  music player loops a track with `SeekL` + `ReadS` without parameters; the head stayed past the end and the
  Load Game screen hung at frame 1240 (the worker retried GetlocL forever within one frame).

- **XA audio: the music and the voices** (`shims/audio.c`): while the game streams XA (ReadS with CdlModeAP and
  the Setfilter file / channel) the virtual disc reads each sector the head passes **from the disc image**
  (`--disc PATH`, default `game/usa.img`, which `tools/disc_fetch.sh USA` keeps: the extracted XA files lost the
  sector subheaders), finds the file there through the ISO 9660 directory, and hands the channel's audio sectors to
  the XA ADPCM decoder (psx-spx; 37800 / 18900 Hz, mono / stereo, 4 / 8 bits), queued at 37800 Hz and resampled to
  44100 Hz stereo, 735 frames per vblank: to the `--window` viewer's audio pipe and to `--dump-audio FILE.wav`. The
  head moves 150 sectors/s at double speed (2.5 per vblank; stage 1 moved it 3 per vblank, so the voice clips end a
  little later than in stage-1 runs and the frames after the first clip differ from those runs). CD mix / volume
  from SpuSetCommonAttr, CdlMute / CdlDemute. Checked: the A00 play script gives 1321 XA sectors decoded and 150 s
  of non-silent 44.1 kHz audio in 177 s (music: RMS 3000-9000, smooth waveform, 1-3.5k zero crossings/s); the
  viewer receives it (`--viewer-arg --stats`: audio queued ~20 ms). Not yet: movie audio, the title music of the
  skipped opening movie; no XA in the attract demos (as far as the port can tell, they stream none).
- **Sound effects and sequences** (`shims/sound.c`, T1 `port/shims/sound.c`): a software SPU (24 voices, SPU
  ADPCM, ADSR, pitch) and libsnd at its API: `SsVabOpenHead` + `SsVabTransBody` (the game's bank loading,
  func_800753D4) place the banks in sound RAM, `SsUtKeyOnV` / `SsUtKeyOffV` / `SsUtSetDetVVol` play the effects
  on the voices the game names, `SsSeqOpen` / `SsSeqPlay` the jingles. Mixed with the XA audio every vblank (and
  always run, headless too: the game reads the voices' state). Checked: three banks load in the A00 play script
  (4 / 18 / 2 programs), the effects add a smooth signal (RMS ~3300, a continuous ambience in A00), frames
  unchanged. No reverb yet.

- **Free play in A00**: after the opening and the journal tutorial Tomba walks, pushes and jumps onto a barrel,
  walks back, and the "Use up and Circle to look inside" hint appears (the script above; same frames with native
  or interpreted overlays).

### 0.1 Playing it on a PC

**Linux** (x86-64 with 32-bit support, any distribution with the packages below):

```
sudo apt-get install -y git python3 python3-pip cmake ninja-build gcc-multilib libsdl2-dev
git clone <this repository> && cd <it>
bash tools/disc_unpack.sh /path/to/your/Tomba2_USA.bin game/usa   # -> game/usa/ (files) + game/usa.img (image)
bash tools/session_bootstrap.sh --no-build                       # the PS1 toolchain (once; asks for sudo)
bash port/play.sh                                                # matching build, port build, then the window
```

**Windows 10 / 11: through WSL2** (the port is an i386 Linux program that maps the PS1 RAM at its own address;
WSL2 runs it unchanged, WSLg shows the SDL2 window and plays the sound):

```
wsl --install -d Ubuntu-24.04        # in an administrator PowerShell, once; reboot, open "Ubuntu" from the Start menu
# then in the Ubuntu window, the Linux steps above, with the disc image from the Windows side, e.g.
bash tools/disc_unpack.sh "/mnt/c/Users/YOU/Games/Tomba2 (USA).bin" game/usa
bash port/play.sh                    # options pass through: bash port/play.sh --viewer-arg --fullscreen
```

The disc dump is the player's own: a raw `.bin` (2352-byte sectors; the `.cue` is not needed), a zip or 7z of it.
Saves go to `game/usa/tomba2_mc0.mcd` (`--save-dir DIR` to change). Keys: arrows, X = Cross, Z = Square,
S = Triangle, D = Circle, Q / W = L1 / R1, A / E = L2 / R2, Return = Start, Backspace = Select, F11 = fullscreen,
F = window size, Escape = quit; a game controller works too. Checked here: the same binaries under
`SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy` (no display in the container); not yet checked on a real WSL2.

**A native Windows build** (no WSL) is experimental: it cross-compiles and links, but has **not been run** (Wine
crashes on any program in this container, even a hello world). T1's `sys_win32_i386.c` (Win32 API, a vectored
exception handler instead of SIGSEGV, the PS1 RAM as a section mapped at 0x80000000 / 0xA0000000, the exe based at
0x10000000 and large-address-aware) is taken over with the lookup / stub / interpreter code moved to
`runtime/sys_lookup.c`, shared by both hosts; `gen_t2.py link` skips the stdcall-decorated Win32 imports. T2 maps
the KUSEG mirror by default on Windows too (relaunching itself with the range reserved when Windows has blocks
there, T1's trick): the native code draws through masked KUSEG pointers so much that `--no-kuseg` (every access
emulated in the fault handler) runs about ten times slower (Linux, the A00 script to frame 9700: 49.6 million emulated accesses). The sites are the
primitive builders (`func_8005019C`, `func_8004FFB4`, `func_8007FDB0`, `func_8007FCC8`, SOP's `func_80109C80` /
`func_801099B4` / `func_8010C26C`, A00's `f_DrawTownCreatureGt4Batch` / `Gt3Batch` / `func_80115598`, the
`SetDrawMode` / `LoadImage` shims): T1's generator rewrite of the masked-pointer idioms (`& 0xFFFFFF` ->
`| 0x80000000`, its `port_kuseg_mask`) would remove them. That is the open risk T1 hit on real Windows 10
(blocks of the range in use by the host).

```
sudo apt-get install -y gcc-mingw-w64-i686
cmake -S port -B build/port-win -G Ninja -DCMAKE_TOOLCHAIN_FILE=$PWD/port/cmake/mingw-i686.cmake \
      [-DPORT_SDL2_MINGW=$PWD/SDL2-2.30.11/i686-w64-mingw32]     # SDL2-devel-2.30.11-mingw.tar.gz, for tomba2-view.exe
cmake --build build/port-win                                     # -> build/port-win/tomba2.exe (+ tomba2-view.exe)
```

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
| `runtime/window.c`, `tools/view/tomba2_view.c` | `port/runtime/window.c`, `port/tools/view/tombi_view.c` | names, 320x240, 60 Hz audio frames (stage 2) |
| `shims/card.c` | `port/shims/card.c` | `tomba2_mc*.mcd` in `--save-dir` (default the data dir), T2's libcard names (stage 2) |
| `shims/sound.c` | `port/shims/sound.c` | `SsVabOpenHead` + `SsVabTransBody`, `SsUtSetDetVVol`, `SpuWrite`, output through `audio.c` (stage 2) |
| `shims/audio.c` | new | XA ADPCM from the disc image (psx-spx), the 44.1 kHz output, the CD mix (stage 2) |

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

## 5. Open points (stage 3)

Stage 1's list is done except where noted: the 5637 crash, free play in A00, the overlays' C and the GTE asm
natively, the SDL2 window and 60 Hz pacing, XA audio, sound effects, the memory card (§0).

1. **Check on real hardware**: `bash port/play.sh` on a desktop Linux and on WSL2 (window, keyboard / controller,
   sound latency, the pacing line at exit); a save at a save point and a load from the title (the card shim is
   only checked as far as "No data" here).
2. **Movies** (`OP.STR`, `LOGO.STR`, `END.STR`: skipped): T1 `port2/shims/mdec.c` + the `St*` ring over the disc
   image, with the movie's XA audio through `shims/audio.c`.
3. **More of the game**: scripted runs into other areas (A01..A0L, the area overlays are native already) and
   their boss / minigame overlays; each crash hunted with `--no-ovl-native` frame diffs, `--ovl-interp`,
   `--interp-range` and gdb (§0). MAIN's 21 functions the host compiler rejects and the overlays' 20 (generated
   `dropped_<prog>.txt`) stay interpreted; MAIN's own asm (main() = func_80050B08, 228 functions) too until matched.
   Still unhandled in general: a `void` C function whose asm callers read `$v0` (`func_8001CE90` passes
   `func_8001CE04`'s result on; it works because the native epilogue keeps `eax`).
4. **Reverb** and the remaining libsnd calls (`SsSetReservedVoice`, `SsSetStereo`, ...) in `shims/sound.c`.
5. **Native Windows**: WSL2 for now (§0.1). The experimental exe (§0.1) needs a first run on real Windows (or a
   working Wine): the KUSEG mirror, the viewer pipes, the pacing; the long-term answer is the native-pointer port
   once the decomp is complete.
6. The boot exe (`SCUS_944.54`: legal screen, then it loads MAIN.EXE) is skipped; running it first would need its
   own symbol table in the port.

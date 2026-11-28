# Native port (PC first)

The port compiles the matched C of `src/` for the host and runs it against the player's own game files. It is built
the way the first game's project built its port (Tombi-Decomp, same author, MIT: `port/` and `port2/`, documented in
its `docs/PORT.md`); the code that is copied from there says so at the top of each file, and THIRD_PARTY_NOTICES.md
credits it. Nothing of the game is in the repo: the port reads the player's disc image (`--disc`, default
`game/usa.img`; or the extracted `game/usa/`) at run time.

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

**Windows without WSL**: the native build of §0.2 (a zip with `tomba2-launcher.exe`).

### 0.2 Stage 3 (2026-11-28): the Windows build

The player's zip, `Tomba2-port-win32.zip` (built by `bash tools/port_win_package.sh OUT.zip [SDL2_MINGW_DIR]`;
never committed): `tomba2.exe` (the game, i386, freestanding on the Win32 API: T1's `sys_win32_i386.c`),
`tomba2-view.exe` (the SDL2 window, keyboard / XInput controller, sound), `SDL2.dll` (2.30.11), `tomba2-launcher.exe`,
`README.txt` (port/README-windows.txt: the player's steps and the controls), `LICENSE-SDL2.txt`. The player unzips
it, double-clicks `tomba2-launcher.exe`, picks the disc image once (remembered in `tomba2-launcher.ini`; Shift at
start picks another), and plays; memory cards in `saves\`, the log in `tomba2.log` (beside the launcher, or in
`%APPDATA%\Tomba2-port` when that folder is not writable). 64-bit Windows 10 / 11 (the 32-bit exe needs the 4 GB
address space WOW64 gives a large-address-aware program). Nothing of the game is in the zip.

```
sudo apt-get install -y gcc-mingw-w64-i686 zip            # + wine wine32:i386 to test (below)
python3 tools/build.py                                     # the generator reads build/*.elf, build/*.bin, asm/ at build time only
bash tools/port_win_package.sh build/Tomba2-port-win32.zip  # downloads SDL2-devel-2.30.11-mingw (sha256 checked) when no dir is given
# test bed: Wine 9.0 (Ubuntu wine32) aborts with "free(): invalid pointer" unless the XDG runtime dir exists
mkdir -p /run/user/0 && chmod 700 /run/user/0
WINEPREFIX=$PWD/build/wp WINEARCH=win32 WINEDEBUG=-all wine build/port-win/tomba2.exe --frames 3000 --dump-frames D --dump-every 100
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy WINEPREFIX=... wine build/port-win/tomba2-launcher.exe   # with a prepared .ini
```

What stage 3 changed (each with its check):

- **The disc image is the only input** (`shims/cd_virtual.inc`): `--disc PATH` takes a raw `.bin` / `.img` (2352-byte
  sectors, mode 2 or 1, told by the sync pattern), a `.cue` (its first `FILE`, relative to the .cue, quotes and
  either separator) or a cooked `.iso` (2048-byte sectors: no XA audio). `CdSearchFile` finds every file in the ISO
  9660 directory and reads it from the image; `MAIN.EXE` too, checked by SHA-1 (`f41c4065...`, USA SCUS-94454; the
  EU `6bcee82b...` and ES `410bd51f...` ones are named in the error, `--no-verify` runs another anyway); a file that
  is no CD image is refused with its reason. Without `--disc` the port tries `game/usa.img`, then the extracted
  files of `--data` (stages 1-2). The virtual sector layout is unchanged, so the frames are the same as from the
  extracted files (attract mode 3000 frames, the .cue and a converted .iso checked too). Saves go beside an image
  named with `--disc` unless `--save-dir`.
- **No KUSEG mirror needed** (the open risk of stage 2, T1's lesson). Windows keeps its own memory in 0x10000-0x1FFFFF
  (Wine: 0x110000-0x1FFFFF committed; T1's Windows 10 user: 0x10000-0x60000, 0xB0000, 0xC0000) and an access to a
  committed block reads the host's data silently. The masked pointers native code dereferenced: (1) the primitive
  buffer pointer `D_800BF544`, set every frame by main() (asm) to `(D_800BFE68 + i * 0x14000) & 0xFFFFFF`: the
  interpreter stores its KSEG0 view (`mips_interp.c kcell`), gen_t2.py `kuseg_link_stores` keeps the 24-bit OT links
  native code stores (`*o = (u32)p;` -> `& 0xFFFFFF`, 96 sites, T1's rule) and `DrawOTag` ignores a 0x80 an
  interpreted link store leaves in a tag's length byte; the GPU shims (`LoadImage`, `SetDrawMode`, `SetDrawArea`,
  `DrawPrim`, `ClearOTag(R)`, ...) take KUSEG buffers through KSEG0; (2) the actor animation pointer at +0x38, whose
  bit 31 is a flag ("blend in progress", cleared by func_80075FF8 with `& 0x7FFFFFFF`, tested `>= 0` by
  f_AdvanceActorSkeletalAnimation), so it holds the KUSEG view of the animation data (0x00018456 for MAIN's tables,
  0x0014D3F0 for A00's): gen_t2.py `kuseg_field38` reads it through `port_kptr` (port_prelude.h) wherever it is
  dereferenced (89 sites + A01's `->p38`; stores, comparisons, address-of left alone). Check: Linux with
  `--no-kuseg` (no mirror, every low access emulated and tallied): 10.6 million accesses in 3000 attract frames
  before, **0** after over 20000 attract frames and the 10600-frame A00 script, same frames, full speed. Under Wine
  before (2): 8 of 80 attract frames differed (an eye blink, smoke particles: A00 / A01 creatures reading their
  animation through Wine's heap). Windows maps no mirror by default (`--kuseg-mirror` maps it where free); free
  blocks are reserved and guarded (an access is served from KSEG0 and counted at exit), and the exe still relaunches
  itself with the range reserved when Windows has blocks there.
- `port_low_emulate` handles `mov moffs` (`a1` / `a3`): `func_80051E00` reads the BIOS TCB pointer at 0x110, page 0
  is never mapped on Windows (first crash under Wine, frame 3).
- **No game bytes in the exe**: the overlay funcmap held each function's first two retail code words (to tell the
  resident overlay); it now holds two FNV-1a hashes of those 8 bytes (`sys_lookup.c code_hash`): same interpreted-call
  counts and frames.
- **tomba2-launcher.exe** (`port/tools/launcher/tomba2_launcher.c`, plain Win32 + comdlg32, statically linked
  runtime): the role of T1's `tombi-port.exe` without Python: a file dialog for the image, the .ini, `tomba2.exe
  --disc IMAGE --window --save-dir saves <options=>` without a console (stdout / stderr to `tomba2.log`), and on a
  non-zero exit the FATAL line with "choose another disc image?". Checked under Wine: unzipped into a folder with a
  space in its name, a prepared .ini, SDL dummy drivers: the game ran 900 frames paced at 59.2 vblank/s, the viewer
  received them (its own `--dump`), the log and `saves\` were made; the dialog itself was not clicked (no display).

**Checked under Wine 9.0 (wine32, WINEARCH=win32), the exe against the Linux build, frame dumps byte-identical**:
attract mode 20000 frames (80 dumps: title, demos in A00, A01, A03), the A00 play script of §0 (10600 frames, 53
dumps: New Game, story text, opening, journal tutorial, free play), the `.cue` path, the error paths (no CD image,
the EU MAIN.EXE). The window under Wine with `SDL_VIDEODRIVER=dummy`: frames arrive, 58.4 vblank/s. **Not checked**:
a real Windows 10 / 11 machine (the window, the controller, the sound device, SmartScreen, which KUSEG blocks it
commits), the file dialog by hand, long play past A00.

### 0.3 Stage 4 (2026-11-28): the user's first real-Windows run

The user's report: "it starts, but it is full of graphical errors, and it does not save the game"; their
`tomba2.log` (a 13293-frame run on Windows 11 at 59.18 vblank/s, no crash) showed CRD.BIN loaded at frames 10433 and
10851 and then the interpreter nearly idle (~650 calls per 100 frames, a static screen).

- **Saving** (`shims/card.c`): CRD.BIN's save (`func_8018AEB8`) creates the file with `open(name, 0x10200)` (one
  block), then opens it with `0x8002` (O_NOWAIT | write), clears the four SwCARD events with TestEvent and writes
  0x980 bytes; the load (`func_8018B660`) opens with `0x8001`, seeks to 0x380 and reads 0x600 the same way. On the
  console the BIOS returns at once and raises SwCARD (0xF4000001) "I/O end" (spec 4) when the transfer is done; the
  shim did the transfer but raised nothing, so CRD waited for ever on "Saving game..." (reproduced headless with
  the user's numbers). An O_NOWAIT read / write now raises I/O end (a failed one SwCARD error, 0x8000). Checked:
  save, then a fresh run Title -> Load Game -> "Load Completed" -> A00 at the saved place (commands below).
  The save screen is reached from the pause menu's Load data with CRD's mode byte (D_800BF498.x3C, 0x800BF4D4:
  0 load from the pause menu, 1 save as from a save point, 0x81 load from the title) poked to 1 while CRD starts:

```
P=""; for f in $(seq 9448 2 9478); do P="$P --poke $f:800BF4D4=1"; done
build/port/tomba2 --frames 10100 $P --save-dir S --dump-frames D --dump-every 10 --pad-script \
  400:start,600:cross,800:cross,1000:cross,1200:cross,1400:start,6000:circle:10x50/60,9300:start:10,9400:down:4,\
9440:cross:4,9700:cross:4,9800:cross:4,9850:left:4,9880:cross:4      # slot 1, file 01, "OK to save?" Yes
build/port/tomba2 --frames 1700 --save-dir S --dump-frames D2 --dump-every 10 --pad-script \
  300:right:4,400:cross:4,700:cross:4,900:cross:4,1000:left:4,1050:cross:4      # Load Game, slot 1, file 01, Yes
```

  Test hooks for scripted runs: `--poke FRAME:ADDR=BYTE` (repeatable, 16), `--trace-pos N` (the player actor's
  position, 16.16, every N vblanks). The save point actor is MAIN's func_800739AC (A00 has two, at x 4200 / 14870).
- **Psy-Q math** (found with the reference emulator, docs/EMU.md "Port vs emulator: findings"): the shims of
  ratan2, SquareRoot0, csqrt, RotMatrix, ApplyMatrixLV, ApplyRotMatrix and RotTransPers were exact or rounded
  differently from Sony's code, so the camera angle (f_RebuildCameraViewTransform, attract demo 1 frame 1216) and the
  vertex positions left the retail ones; they are removed and the retail libgte code is interpreted (pure). The
  kept shims (rsin, rcos, RotMatrixX / Y / Z, MulMatrix0, ApplyMatrix, ApplyMatrixSV, the Set* register loads) are
  equal on every input `tools/emu_shimcheck.py` tries. The A00 script still runs the same route (47 s headless).
  MulMatrix0, ApplyMatrix and ApplyMatrixSV are interpreted too: their results were equal, but the retail code loads
  its matrix into the GTE rotation registers and leaves it there, and game code runs RTPT on it afterwards
  (func_8007FDB0, the area models: attract demo 1 frame 1219). Found by `emu_compare.py --ram-at`, then the first
  differing store to the scratchpad word 0x1F800080 (NCLIP results): a gdb `watch` in the port (`port_frame`,
  `port_mips_cur_pc`, `info symbol $pc`) against `cpu.set_store_hook` in the emulator loaded from `--save-state` at
  1218. After the fix the attract route's RAM equals the emulator's up to frame 1220; at 1221 the sound engine's voice
  table (0x800BE31D, one byte per voice) differs because the port's SPU keys voices on where the emulator reports
  every voice off (docs/EMU.md), and the game's state follows that from there (pictures differ from frame 1240).
  `--keys-off` (a test option: SpuGetAllKeysStatus reports every voice off, as the emulator) removes that: with it
  the attract route's RAM equals the emulator's up to frame 1250 at least, and the first difference is the
  rasteriser's (frame 1250, the A00 demo's fade-out: identical GP0 packets, a few texels on textured gouraud
  polygons; the port rounds texel coordinates to nearest, tools/psxemu/gpu.py truncates).
- **GTE** (`runtime/gte.c`): RTPS / RTPT divide with the hardware's UNR table and two Newton steps (psx-spx; as
  tools/psxemu/gte.py) instead of the exact quotient; NCS / NCT / NCDS / NCDT / CC / CDP added (none was logged as
  missing on the routes checked). `python3 -I tools/gte_diff.py [--n N] [--ops RTPS,...] [--raw]` compiles gte.c
  with a driver (build/gte_diff/drv, gcc -m32) and compares every register after each command with gte.py on random
  states: 0 differences in all 22 commands (6000 states).
- **SetDrawArea** (`shims/gpu.c`): it now writes E4 (bottom right) as well as E3, as the retail code does; the
  stale second word left the game's clip windows open on the right and bottom (attract demo 1: the vitality HUD's
  32-pixel window at x 144 showed two bombs instead of one). T2's names of the libgpu encoders
  (`f_EncodeGpuDrawAreaTopLeftCommand`, `f_EncodeGpuDrawAreaBottomRightCommand`, `func_80082220` get_mode,
  `func_80082370` get_ofs, `func_8008238C` get_tw) are shims too (they were logged stubs returning 0 for retail
  callers such as SetDrawEnv). The emulator still stubs them (its DR_AREA packets are zeros).
- **Rasteriser check by packet replay**: with RAM and packets equal, the remaining picture differences against the
  emulator are one 5-bit step on textured gouraud polygons (gpu.py truncates the interpolated colour / UV, gpu.c
  rounds): a per-packet replay of attract frame 1226 (emulator GPU state + one packet through both rasterisers) shows
  nothing else (320 of 841 packets, all `3c` / `34`).
- **Interpreter page 0**: `mips_interp.c ma` maps every KUSEG address below 0x200000 to KSEG0, page 0 included (an
  interpreted store through a null pointer + 0xA at attract frame 5771 reached the host's page 0: on Windows an
  emulated access, 24 in 6000 frames under Wine). Linux and Wine frames equal (60 attract dumps).
- **The TV window** (`shims/gpu.c tv_frame`): DISPENV.screen is 0,8 256x224 (logged: `[gpu] display 320x240,
  screen 0,8 256x224`): a television shows the display's first 224 lines 8 lines down and never the last 16, where
  the cutscene letterbox leaves the previous picture. The window gets that picture (240 lines, black borders);
  `--dump-tv` dumps it too; `--dump-frames` alone keeps the whole DISPENV area (the emulator's dumps).
- **Viewer** (`tools/view/tomba2_view.c`): every window title is "Tomba! 2 (PC port)" (the launcher's file dialog and
  message boxes too, as T1's "Tombi! (PC port)"); `--renderer NAME` (SDL_HINT_RENDER_DRIVER: direct3d, direct3d11,
  direct3d12, opengl, opengles2, software; SDL's default if it fails), `--linear`, `--fullscreen` (also tomba2
  options, so the launcher's `options=` line takes them); an XRGB8888 streaming texture filled by the viewer (RGB24
  was converted by each render driver); `SDL_RenderSetLogicalSize(320, 240)` keeps 4:3 in any window size; F12
  saves `tomba2_shot_NNN.bmp` in the working directory (the launcher's folder); at start it prints `tomba2-view: SDL
  2.30.11, video driver windows, renderer direct3d (accelerated, vsync; max texture ...; available: ...)` and the
  display mode to stderr, which is tomba2.log under the launcher. Checked with SDL's dummy video driver on Linux
  (the software renderer) and under Wine; not on a real Windows display.

### 0.4 Stage 5 (2026-11-28): the net climb, narrow results, the music

The user's second real-Windows run (build 2): the graphics right, but "it got stuck trying to climb up the wall"
(their screenshot: A00, Tomba on the climbable net beside the tower near the burning house) and the music stuttered
at times (their log: 9447 vblanks at 59.43 vblank/s, direct3d).

- **Reaching the net headless**: the user's memory card (one save at the first save point, 00:00:18) loads to
  x 4190 by the Load Game script of §0.3; the net is on the back lane by the tower (x ~9100-9300, z ~5370), which
  attract demo 1 walks to by itself. `--demo-takeover F` (test hook, `shims/pad.c`): from vblank F the demo's input
  replay (`func_800794C8`: u16 pairs of buttons and game frames at `D_800BED88`, count `D_800BED8C`, demo mode
  `D_1F80019A == 1`) plays the pad script instead, so the demo's own place and state are driven by the script (the
  real pad reads idle; pressing a button on the real pad would end the demo). Same option in `tools/emu_run.py`
  (and `emu_compare.py --emu-args`). `--poke` takes scratchpad addresses too (`--poke 2550:1F80019A=0` ends the
  replay, but the demo then quits to the title on the first press). The climb route:

```
build/port/tomba2 --frames 2760 --trace-pos 10 --demo-takeover 2550 \
  --pad-script 2560:right:40,2600:right+cross:15,2615:right:30,2650:up:400      # walk to the net, jump on, climb
```

- **The bug**: Tomba grabbed the net (y -1346) and stayed there; with `--interp-range all` (the retail code) he
  jumped onto it at x 9347 z 5427 and climbed (y -1839 at frame 2720). `--no-ovl-native` crashed at 2626 (SIGSEGV in
  native code). A bisection of `--interp-range LO-80200000` (LO from 0x80010000 to 0x80100000, 4 runs at a time,
  about 20 s each) ended at `func_80058918` (Tomba's state machine); its RAM against the interpreted run differed
  first at frame 2605 in the player's sub-state (+6: 0 native, 1 retail) in state 21, `func_80065374(a)`: MAIN's
  dispatcher to the area's climb code, `func_8010AECC()` in A00, which A00's symbols name
  `f_UpdateA00TombaVerticalClimb` and which reads the player in `$a0`. gen_t2.py found no arity for the name
  `func_8010AECC` (no program has a function by that name), so the call was not forwarded and A00's code read a
  random stack word as the actor. **Fix** (`all_arity_by_addr`): every `func_XXXXXXXX` name the C uses without an
  arity takes the highest arity of any program's function at that address. Across all 28 programs this added
  exactly this one forwarded call (the generator's `forwarded_*.txt` before and after). **Check**: the port climbs
  (y -1839 at 2720) native, with `--no-ovl-native` (no crash) and interpreted; against the reference emulator
  (`emu_compare.py --frames 2760 --pad-script ... --port-args="--keys-off --demo-takeover 2550" --emu-args="--demo-takeover 2550"`)
  the player actor (0x800E7E80, 0x200 bytes) is byte-equal at every RAM dump from 1300 to 2750, the climb frames
  show the same pose and place, and every other differing byte is a known one (the OT link high bytes, 0x80 vs 0,
  of `kcell`; 0x800A6300 / 0x800BE0D8; the emulator's zero DR_AREA words; the three-bomb HUD of its stubbed
  SetDrawArea).
- **Narrow results read wider by native callers** (found by the broader sweep below: native vs `--interp-range all`
  on a Load Game route, frame 3500: the "2000" AP popup of the Tiny Mouse's House had no digits natively; bisected
  to `func_80040AA4` -> `func_800727D4`, which stores `((s16 (*)(s32, u8 *))f_FormatIntegerText)(ap, buf)` as the
  digit count: the native `u8` function leaves ah undefined, the cast reads ax). The stage-2 extension (`PortFunc.ret`)
  covered MIPS callers only; native callers also read a narrow result wider through casts, through the implicit
  `int` of a renamed (conflicting) definition (`f_CalculateYawFromPositionToPoint` returns s16) and through another
  program's prototype. **Fix** (`narrow_wrapper`): every non-static native function with a char / short result is
  compiled as `NAME__def`, and `NAME` is an asm wrapper that passes eight argument words on (PORT_ARG reads
  included), calls it and extends al / ax as the R3000 code had `$v0` (movzbl / movsbl / movzwl / movswl): 39
  functions. **Check**: the Load Game route (9400 frames) and 3150 attract frames are now pixel-identical to the
  interpreted runs (the attract demo had 7 differing frames of 126 before: its popups), the A00 script of §0 is
  unchanged (212 frames), the native function count is unchanged (4484).
- **`void` definitions whose result is read** (the open point of stage 2): a C definition that matched the retail
  bytes as `void` may still leave a value in `$v0` that its callers use (`func_8006032C` leaves the byte it stored
  last, tested through `((s16)((s32 (*)(u8 *, s32))func_8006032C)(a, k)) == 0`; `func_800493E8` its callee's
  result, read by asm callers in A01 / A04 / A05 / A06 / A08 / A0C). gen_t2.py `void_results_used` finds every
  function whose result some caller reads (an asm caller that reads `$v0` after the `jal` before writing it, a C
  cast with a non-void result, a non-void prototype in any program), and those of them that are `void` in C stay
  retail code: 21 (MAIN 16, A02 1, A05 2, A06 1, A07 1; the list in `sources_report.txt`). Frames of the three routes
  unchanged, same speed (the A00 script in 48 s).
- **Broader sweep** (native vs `--interp-range all`, positions every 5 vblanks + frame dumps): four Load Game routes
  from the user's card (two seeded random walks, a 8000-frame walk right to the Tiny Mouse's House with jumps and
  dialogue, a walk left onto the back lane), 20000 attract frames (demos in A00, A01, A03, twice each: 200 dumps)
  and seeded random play handed over by `--demo-takeover` in the A01 demo (from 4200 to its end at 5880) and the A03
  demo (7100-8690): identical after the fixes. Not reached by play: A01 and later areas outside the demos (the
  story gates them). Windows (Wine 9.0, the new zip): the climb route and 60 attract dumps byte-identical to Linux;
  `--no-kuseg` on Linux: 0 native low accesses on the climb route. Against the reference emulator, the A01 takeover
  (`emu_compare.py --frames 5880 --every 100 --pad-script <seed 11> --port-args="--keys-off --demo-takeover 4200"
  --emu-args="--demo-takeover 4200"`, 466 s): the player actor byte-equal at all 8 RAM dumps (4000-5850), the rest
  only the known differences (OT link high bytes, DR_AREA words, libgpu statics), every BIN/ load at the same frame.
- **Music** (`shims/audio.c`, `tools/view/tomba2_view.c`): the user's log paced 59.43 vblanks/s overall, i.e. the game
  produced ~1 % less audio than the device played; the viewer kept 2-6 frames in its ring and re-primed 33 ms of
  silence at each underrun, so the ring ran dry every few seconds (a test run with SDL's dummy audio driver: the old
  viewer padded 1.8 s of silence in 40 s). Now: (1) the viewer resamples its ring (linear) at a rate that follows the
  smoothed fill (proportional + integral, at most 2 % off), holding ~100 ms queued; an underrun re-primes to the
  target, more than 400 ms queued skips back; every underrun and skip is logged to stderr with the time
  (`tomba2-view: audio underrun #N at T s (queued M ms)`, the first 20 then every 100th; a summary at exit; `--stats`
  adds frames received / played, the longest wait for the game and the lowest fill per second), which is tomba2.log
  under the launcher; the ring is 1.5 s with power-of-two counters. (2) the XA queue of the game starts playing once
  a sector and a vblank (2646 frames, 70 ms) are queued or the stream has paused, and counts a queue that runs dry
  while sectors still arrive (`[port] audio: XA queue ran dry at frame N`, a total at exit): on the A00 script of §0
  it ran dry once (the story-text clip's end; three times without the start-up margin). Checked: a simulated device
  (44.1 kHz, 512-frame pulls) against a game at 59.0-60.6 vblanks/s with jitter: no underrun in 300 s; the dummy
  driver (which plays 2 % fast because it sleeps whole milliseconds): 8 ms padded in 60 s against 1.8 s in 40 s
  before. Not checked: a real sound device (none in the container); the Windows pipe write still blocks if the
  viewer stops reading for more than its 1 MB (6 s of audio).

### 0.5 Stage 6 (2026-11-28): the debug menu, noclip, warp; every area reached

The user asked for a debug menu and noclip like the first game's port (Tombi-Decomp's port2/runtime/debugmenu.c,
MIT, same author: copied and adapted, the same keys, lines, 5x7 font and hook points). `runtime/debugmenu.c`.

- **Options** (all off by default; with none of them every hook is inert, and the frame dumps are byte-identical to
  the build before: attract 3000 frames, 60 dumps, and a Load Game route, 52 dumps + positions every 5 vblanks,
  against a build of the previous commit): `--debug-menu` (the menu), `--noclip` (noclip on from the start, without
  the menu), `--debug-warp FRAME:AREA:SPAWN` (test hook: warp at the first vblank >= FRAME that is in gameplay; AREA
  in hex, 1 = A01, 10 = A0G; implies `--debug-menu`). The launcher: `debug_menu=1` in tomba2-launcher.ini (it has
  no dialog with options; the line is written on the next save of the .ini).
- **Keys**: Select+L1+R1 (pad or keyboard) or F1 in the window (the viewer sends Select+L1+R1 for one sample) opens
  and closes it; while it is open the game gets no buttons. Up / Down pick a line, Left / Right change the value
  (L2 held: steps of 10), Cross applies, Triangle or Start closes; buttons held when it closes are kept from the
  game until released.
- **Lines**: NOCLIP (WALLS), FLY (d-pad moves Tomba in x / z, L1 / R1 up / down, Cross held = 4x), INFINITE
  VITALITY, MAX AP (9999999), WARP AREA (A00-A0L), WARP SPAWN (the arrival index, 0-63), WARP NOW, INFO OVERLAY
  (frame, measured vblanks per second, area-arrival, "(NO PLAY)" outside gameplay; Tomba's x / y / z, vitality / max,
  AP; the cheats on), SPEED (normal; slow: one extra period of sleep per vblank; fast: pacing off). T1's lines that
  T2 has no data for yet are left out (give item, equip weapon, event flags, lives).
- **T2's data** (USA): the player actor 0x800E7E80 (position 16.16 at +0x2C / +0x30 / +0x34, speed +0x44, direction
  +0x48..+0x4C, vitality s16 +0x16E and its HUD copy +0x170, state +4: 1 = running; f_GrantPickupHealth); the game
  state 0x800BF870 (area +0, arrival +1, AP s32 +4 (func_8004B3F4 adds to it), max vitality +0xD (New Game: 4)).
  "In gameplay" = an area overlay resident at 0x80108F9C (`port_ovl_resident`, sys_lookup.c), the player in state 1,
  no transition requested, no attract demo (0x1F80019A != 1). The cheats write only then.
- **Warp**: the transition the game's own exits make (A0A..A0E's boss ends, A0F, MAIN's warp items in
  func_80035218): the destination u16 0x800BF83A = area << 8 | arrival (Tomba2Edit's `DESTINATION`), the request
  0x800BF839 = 1, the scratchpad mode 0x1F800236 = 7 (the fade the exits use). The game then loads BIN/A0x.BIN
  itself (9 vblanks later) and places Tomba from the area's arrival record. A warp to the area already resident
  places him without a load. Memory writes only, from the vblank (as `--poke`): the game's code is never called.
- **Noclip** (`port_lookup` -> `port_debug_hook`, only while noclip is on): `f_ResolveActorRadialTerrainContact`
  (0x80045CAC) and `f_ResolveActorDirectionalTerrainContact` (0x80046E2C), the horizontal terrain probes, return
  0 (no contact) for the player; every other actor and the floor probe (f_ResolveTerrainProbeVerticalContact) are
  unchanged. Both are asm (interpreted) and every call reaches them through `port_resolve_call`, so the hook covers
  native and interpreted callers. What it does: in A09 (spawn 0, walking right) Tomba walks into the rock face
  (x 4677 -> 4800) where he stopped before. What still stops him: the end of the area's walking plane
  (f_ProjectActorOntoAreaPlane: T2 keeps Tomba on 2.5D planes; dropping it would leave him off any plane) and other
  actors' bodies (the barrel NPC in A00 at x 6000). Found with a store trace in the interpreter: when blocked the
  speed (+0x44) is 0, the position is never pushed back.
- **Fly**: while it is on and in gameplay the byte 0x800BF841 (D_800BF808 + 0x39) is set: `func_80059D28` then
  skips the player update (func_8005950C or the area's own: A02, A03, A07, A0K), as the game itself does; the
  vblank moves the position (4 units per vblank, 16 with Cross) and zeroes the speed. The camera follows, Tomba is
  drawn in his last pose. Off (or a warp) clears the byte; Tomba then falls / lands from where he is. (A
  `port_lookup` hook of func_8005950C does not work: func_80059D28 calls it directly, native to native.)
- **Overlay**: drawn into the RGB copy of the displayed frame that the window or a frame dump gets (shims/gpu.c,
  before the TV window shift), never into VRAM, so the game cannot read it back (T1 filled VRAM).
- **Every area** (`--debug-warp 1500:AREA:SPAWN` after the Load Game route of §0.3 from the user's card, then
  walking right 200 vblanks, three jumps, left 150, right + jump; 3400 frames, positions every 5 vblanks, 34 frame
  dumps): A00..A0L spawn 0 all load and play (A03 the trolley race with its countdown, A0A..A0E the boss intros,
  A0L the ending scene), native and `--interp-range all` identical in positions and in every dump. Spawns 1, 2, 3
  and 5 of every area too (each places Tomba elsewhere): 110 warps, no crash, native = interpreted in all of them
  (positions every 5 vblanks, 34 dumps each); nothing to fix. A run with every line used (menu, noclip, fly,
  overlay, a warp to A03) under Wine 9.0 with the new zip: positions equal to Linux, the 120 dumps equal except
  the measured vblank rate in the overlay's first line; `--no-kuseg` with a warp to A04: 0 low accesses. Not done: the areas past their first minutes
  (bosses fought, story events), the debug menu on real Windows.

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
| `runtime/sys_win32_i386.c` | `port/runtime` | no KUSEG mirror by default (`--kuseg-mirror`), the relaunch kept for guarding (stage 3) |
| `tools/launcher/tomba2_launcher.c` | new (the role of `tools/port_launcher.py` / `tombi-port.exe`) | plain Win32: disc dialog, .ini, log, error box (stage 3) |

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
   A `void` C function whose asm callers read `$v0` (`func_8001CE90` passes
   `func_8001CE04`'s result on): since stage 5 such definitions stay retail code (§0.4, `void_results_used`), and
   narrow (char / short) results are extended for every caller (`narrow_wrapper`).
4. **Reverb** and the remaining libsnd calls (`SsSetReservedVoice`, `SsSetStereo`, ...) in `shims/sound.c`.
5. **Native Windows** (§0.2): runs under Wine frame-identical to Linux; a first run on real Windows is next (the
   window, controller, sound, pacing; the log's `KUSEG blocks committed by Windows` line and the tally at exit say
   whether a masked pointer is still read through host memory). New mask idioms show as `--no-kuseg` sites on
   Linux: add them to gen_t2.py (`kuseg_field38`) or to `kcell`. CHD images are not read yet (T1 reads them). The
   long-term answer is the native-pointer port once the decomp is complete.
6. The boot exe (`SCUS_944.54`: legal screen, then it loads MAIN.EXE) is skipped; running it first would need its
   own symbol table in the port.

# Status and open tasks (hand-off between Claude Code sessions)

Update this file whenever something lands or a task is decided. Newest first.
The step-by-step plan is docs/ROADMAP.md (tick its boxes as steps land).

## 2026-11-14 (3): jump tables in C, NON_MATCHING equivalent C

- **Switches with a jump table can go to C** (`tools/jtbl.py`, called by `tools/build.py` through `cc.compile_c(...,
  asm_filter=)`): the compiler's own table is dropped from the assembly, the code is pointed at the retail
  `jtbl_<addr>` that stays in the program's rodata, and the case labels get the global `.L<addr>` names that table
  refers to (the same names `jlabel` gives them in asm). The table is found by shape (length and which entries are
  equal) among the retail tables whose labels fall inside the function. Measured before: 878 pending functions
  (824 KB, about a third of the pending bytes) use a jump table. `tools/ccheck.py` needs nothing (it ignores
  relocated fields).
- **Decision (user, 2026-11-14): the project stays byte-matching only**; no NON_MATCHING blocks in src. The tool below
  is kept for later but not used.
- **Equivalent C behind NON_MATCHING** (`tools/nonmatching.py FILE.c [--prog] [--note]`), for the native port: the
  function goes in `#ifdef NON_MATCHING <C> #else INCLUDE_ASM #endif`, so the matching build keeps the retail asm.
  The tool refuses a function that matches, checks the matching build and that the file compiles with
  -DNON_MATCHING. The C is not verified byte for byte (the comment says how many words differ): it has to be tested
  in the port. `tools/install_c.py` replaces the whole block once the function matches; `tools/sync_src.py` keeps the
  block with its INCLUDE_ASM line; `tools/progress.py --phases` shows the bytes "with equivalent C" in a last column.

## 2026-11-14 (2): Phase 2 under way (user chose B: engine first, library in parallel)

All code in C: **1532 / 7011 functions (21.9 %, 4.7 % of the bytes)**; Phase 2 MAIN 419 / 1167 (36 %); Phase 4
areas 711 / 4816; library 393 / 867 (incl. asm by design). 29 / 29 byte-identical. `python3 -I tools/progress.py --phases` gives the per-phase table.
- Late in the session: MAIN hand batches of 5-6 functions of 20-35 instructions (smallest INCLUDE_ASM first, skipping
  jump-table switches and the handwritten GTE ones) land about 70 % on the first or second try.
- **Best lever at the end of the session: copies.** Area overlays carry many copies of the same function; one written
  by hand is then installed in every program by `tools/dupsweep.py --install` (it renames the callees and globals to
  each program's names and takes every declaration of the source file). `tools/dupgroups.py` picks the targets:
  group the pending functions by masked word sequence (as funcstats) and take the groups with most copies and few
  bytes. Example: func_80146478 (permuter-assisted) went into 14 programs at once.
- `tools/install_c.py` cannot take K&R definitions yet; callers that pass fewer arguments than a new prototype
  (m2c drops pass-through ones) then fail to compile: give those callers the full argument list instead.
- Every overlay and boot is now a splat `c` segment (`src/<prog>/<prog>.c`), swept like MAIN.
- Sweep (`tools/sweep.py`) improvements, each measured: compilable m2c drafts (`--valid-syntax`, `include/m2c.h`);
  scratchpad variables as symbols (`config/scratchpad.ld` defines every D_1F8xxxxx; drafts declare
  `extern s8 D_1F8xxxxx[]`); missing leading parameters filled; volatile-globals variant; clashing global types go
  through linker aliases (`config/aliases_<prog>.ld`); **parameter counts guessed from the asm** (`tools/arity.py`) in
  m2c's context, so pass-through arguments are kept (the biggest single gain after --valid-syntax).
- Hand decompilation: ~90 MAIN functions, written in scratch files and installed with `tools/install_c.py FILE.c`
  (replaces INCLUDE_ASM lines, adds the declarations before the first use, aliases clashing globals, leaves
  prototypes out because asm drafts call functions with m2c's argument counts). Recurring fixes, worth trying first:
  a global/scratchpad store that must not move into a delay slot -> `volatile`; constants loaded in the wrong order
  -> hold them in local variables (`u32 end = 0xFF`); a base+offset access the compiler folds -> struct field or
  array element; branch layout -> swap the if/else or early return; argument registers passed through untouched ->
  give the function all four parameters; three `lw` + three `sw` through one base (also an argument spilled to its
  home slot and reloaded after a call) -> a struct copy (`Vec3` passed or assigned by value); `v = (x == K) ? 0 : 1`
  turned into `sltu` while retail branches -> still open (func_8001CBA8).
- Script-state steps (`switch (p[0x78])`: case 0 sets up and advances, case 1 waits) match with the shared
  `return 0` as a label inside the switch: `case 0: ...; goto end; case 1: if (done) return 1; end: default:
  return 0;` (func_800425FC, func_8004201C). When case 0 sets the state to 1 and retail reuses the register
  that held the compare constant, the source was `p[0x78]++` (gcc knows the value is 0 there): writing `= 1` or
  `s32 one = 1` gives a v0/v1 swap (func_80117EC8 and its 7 copies, func_8006585C, func_8003A3E8).
- More recipes from this session: a global read that retail does before a run of stores -> read it into a local
  first (the stores might alias it); a callee that receives the caller's argument untouched (`jal` with no
  `move a0`) -> pass that argument explicitly, or call with no arguments when the K&R declaration is in use
  (f_ResolveEffectEightByteStreamPayload(a)); `p = *x; *y = p; if (p == 0)` instead of re-reading; a 0x20-byte
  frame larger than the code needs -> an unused local of that size; a `goto` into the shared `return 0` /
  `*start = 0` tail of an if-chain (f_GetPauseMenuEquipmentGroupRange); an array member of a struct (`->parts[i]`)
  for `base + index` operand order.
- A scratch file that matches can still fail once installed when main.c has no prototype (or a K&R one) for a
  callee whose prototype in the scratch file narrows an argument (s16): cast the argument in the call instead.
- A `switch` whose jump table sits in MAIN's shared rodata does not link once the function is in C (the table's
  `.L` labels vanish): leave such functions in asm until rodata is migrated per function.
- Headers: `include/game.h` GameState (itemCounts at +0x244, appleBits +0x544, flag words), WorkerState,
  CameraState (`g_CameraState`, a linker name for 0x800E8008), PopupRequest / PopupDisplayEntry, MessageBank;
  named scratchpad variables in config/undefined_syms.ld; `include/actor.h` (not yet used).
- The permuter rarely helps on raw drafts (about 10 matches in some 150 near misses at 60-120 s each).
- `tools/dupsweep.py` also installs copies that differ only in instruction immediates (the masked key groups them:
  the same code with other sound / effect ids): it maps each differing immediate and rewrites that literal of the
  C when it appears once (`imm_map`, `patch_consts`); 18 more copies at once. It keeps the linker-global names of
  config/undefined_syms.ld (g_CameraState, ...) instead of renaming them to a program's D_ name, falls back to
  install_c.py for type clashes, and `-v` says why a copy was not taken.
- Library: string literals now become the retail strings' symbols, objects with extra text are rejected (+4).
- Known left-overs worth a look: f_LoadResourceChunkIntoGroup, f_ReleaseActorModelParts (lui order), func_8003F2F8, func_8003F31C, func_8004D8B0, func_8006914C (near misses written by hand, in no file yet).

## 2026-11-14: Phase 1 (Psy-Q library), partly done

- 1.1 / 1.2 done. 1.3: **314 of 867 library functions in C, 71 asm by design, ~480 left** (`python3 -I tools/progress.py`).
- Layout: the library range of MAIN and boot is one splat `c` subsegment per function (`tools/libsplit.py`),
  `src/<prog>/psyq/<lib>/<name>.c`; each file can carry `// CC`, `// FLAGS`, `// ASPSX`, `// AS gnu` (tools/cc.py);
  library files are padded to their retail size (objects end on 16 bytes). `config/aliases_<prog>.ld`: addresses of the
  names that C from other projects uses (`tools/libsweep.py` reads them off the retail code).
- Tools: `name_lib.py` (signature names), `libsweep.py --install` (candidates from psx_tomba `ptsrc.py`, Tombi-Decomp,
  m2c with typed Psy-Q context, MAIN for boot; under 8 compiler set-ups), `libnear.py` + `libpermute.py` (near misses
  + decomp-permuter), `asm_by_design.py`, `sync_src.py` (keeps main.c in step after re-splits), `t1match.py`.
- External, fetched, never committed: psx_tomba (/tmp/psx_tomba, its headers to include/pt and include/psyq), psyz
  (/opt/psyz: Psy-Q 4.0 decomp, MIT), Psy-Q 4.0/4.7 SDK headers (/opt/psyq_sdk, psyz's release assets).
- Known: some library functions match alone but not linked (CdComstr, CdIntstr, ClearImage2, SetDispMask, RotMatrix,
  RotTransPers, SetGeomScreen, PadInfoAct, _padClrIntSio0, rcos): to look at.

## 2026-11-13 (5): Phase 0 tooling, first automatic sweep

- 0.1 `tools/ccheck.py`: checks the function length too; `--func NAME`; INCLUDE_ASM functions skipped unless `--all`.
- 0.2 `tools/decomp.py NAME [--check] [--write]`: m2c draft with `include/*.h` as context (m2c in /opt/m2c).
- 0.4 `tools/sweep.py [--max-size 0x100] --install`: drafts every pending function, installs the ones that match as
  drafted (function + its `extern` lines), keeps only what leaves the linked build OK.
- Result: **41 / 1739 MAIN functions in C** (39 from the sweep). m2c drafts with no types: they will be cleaned up
  as headers grow (2.1).
- Left from the sweep: `func_8004DBB0` (extern type clash), `func_80083AF8`, `func_80086604`, `func_80092B9C`,
  `func_8009413C` (match alone, change the linked build: check rodata).
- 0.3 `tools/permute.py NAME --src FILE.c [--seconds N]` (decomp-permuter in /opt/permuter): matched
  `f_TestAppleCollectedBit` at once. First header: `include/game.h` (GameState at 0x800BF870, apple bits at +0x544).
- 0.5 deferred to Phase 5 (docs/ROADMAP.md). **42 MAIN functions in C.**
Next: Phase 1 (Psy-Q library names and C).

## 2026-11-13 (4): C in the linked build

- `config/main.yaml`: the text is a `c` subsegment, `src/main/main.c` (generated once by splat, now hand-edited:
  one `INCLUDE_ASM("asm/main/nonmatchings/main", NAME)` per function not yet in C). `include/common.h` holds
  INCLUDE_ASM (maspsx-keep) and the basic types.
- `tools/build.py` compiles `.c` with the game's pipeline (gcc 2.8.1 cc1 `-O2 -G0 -funsigned-char`, maspsx 2.79,
  as -O1); still **29 / 29 OK** with `f_StopVoicePlayback` and `f_SetIdentityMatrix` compiled from C.
- `tools/progress.py`: functions / bytes now in C per program (2 / 1739 in MAIN).

How to decompile a function: replace its INCLUDE_ASM line in `src/main/main.c` by C (declarations at the top of the
file for now), check quickly with `tools/ccheck.py src/main/main.c` (or a scratch file with just the function), then
`python3 tools/build.py main --no-split` must print OK.

Next: headers (`include/` game structs from Tomba2Edit names), split main.c into files when areas of the code are
understood, permuter, the boot exe and small overlays to `c` the same way.

## 2026-11-13 (3): reference switched to USA SCUS-94454

User's decision, because Tomba2Edit / Tomba Club work on USA addresses. `config/*.yaml` = USA (29 / 29 OK),
`config/eu/` = EU (29 / 29 OK, `tools/build.py --version eu`, asm in `asm/eu/`). Load addresses are found per version
by `tools/gen_configs.py`. Names: USA 886, EU 885; fixed a bug of the first import (names parked by Tomba2Edit on one
shared address had been taken: now dropped). Probe C still matches on USA. USA: 7037 functions, 5161 game functions,
2.31 MB (docs/PLAN.md). `tools/disc_fetch.sh` now keeps the USA image (`game/usa.img`) on a fresh download; no tool needs it yet.
Open: the 118 Tomba2Edit `FUN_*` starts that are not starts in our split (docs/TOMBA2EDIT.md).

## 2026-11-13 (2): Tomba2Edit names, compiler found

- Tomba2Edit reviewed (docs/TOMBA2EDIT.md): **899 EU functions named** (later corrected: see above) from its USA symbols and USA->EU maps
  (`tools/import_names.py`, `// t2e` lines); overlay load addresses confirmed; container formats documented.
- **Compiler: Psy-Q 4.4 = gcc 2.8.1 + ASPSX 2.79** (docs/COMPILER.md). First two functions matched in C
  (first in `src/main/ccprobe.c`, now in `src/main/main.c`; checked with `tools/ccheck.py`: compile + word compare, relocated fields masked; it does
  not yet check that the retail function has the same length).

Next:
1. C in the linked build (now on USA): switch `config/main.yaml` to a `c` subsegment layout (per-file `INCLUDE_ASM`, splat
   `asm/nonmatchings`), compile with the 2.8.1 pipeline in `tools/build.py`, keep 29/29 OK.
2. Headers: game-state struct at `D_800BFFC0`, actor struct (from Tomba2Edit's names: `f_SetActorAnimation` writes
   +0x46, +0x79, reads +0x7C), Psy-Q 4.4 headers.
3. Permuter (`tools/permute.py` from T1) for the two near-misses in docs/COMPILER.md.
4. Name the Psy-Q functions (signature hits) where Tomba2Edit has no name.

## 2026-11-13: repo bootstrap, disc survey, all-asm matching build

Done:
- Repo set up from Tombi-Decomp's tools (CLAUDE.md, README, .gitignore, `tools/session_bootstrap.sh`,
  `tools/disc_fetch.sh`, `ci_download.sh`, `disc_unpack.sh`, `isoext.py`, `setup_native.sh`, `setup_psyq.sh`,
  `psyq_cc.sh`).
- The three discs surveyed: docs/DISCS.md. ES and USA are separate builds (98 % / 96 % of EU functions found).
- Psy-Q version: **4.4** (object signatures; 245 objects / 117 KB in MAIN.EXE).
- splat configs for all 29 EU programs (`tools/gen_configs.py`: boot, MAIN, 28 overlays) and `tools/build.py`:
  **29 / 29 rebuild byte-identical** from disassembly.
- Function census (`tools/funcstats.py`): 7051 functions, 858 Psy-Q, 1019 exact dups, **5174 game functions /
  2.31 MB**. Plan: docs/PLAN.md.

Decisions (confirmed by the user 2026-11-13):
- Reference version EU SCES-02147 (changed to USA, see above).
- No decomp.dev report / report CI: progress is measured locally (tools/funcstats.py, later a local progress script).
- Layout (left to Claude): `game/<eu|es|usa>/` = the disc's files (only `game/eu.img` kept), `config/<prog>.yaml` per program,
  `asm/`, `build/` generated. Per-version configs will go to `config/<version>/` as in T1.

Next:
1. (done, see above) compiler identification.
2. Name the Psy-Q functions in `config/symbol_addrs_main.txt` / `_boot.txt` from the signature hits.
3. Find the overlay loader in MAIN.EXE (confirm 0x80109D84 / 0x80106D80 / 0x80188000).
4. Container formats (TOMBA2.IDX/DAT/IMG/SND) for the port; tools/psxemu profile for T2.

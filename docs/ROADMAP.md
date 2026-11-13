# Roadmap

Step-by-step plan from the current state (2026-11-13: USA reference, 29/29 programs byte-identical, C pipeline in the
linked build, 2 functions in C) to a fully matched decomp and a native port. Each step has a **done when** test. Work
top to bottom; a phase can start before the previous one is fully closed only where noted. Numbers: docs/PLAN.md.
Keep the checkboxes and docs/STATUS.md current.

Rules for every step: the matching build stays 29/29 OK (`python3 tools/build.py`), work goes straight to master,
nothing from the disc is committed.

## Phase 0 — Tooling (before writing C in volume)

- [x] **0.1 Function length check in `tools/ccheck.py`**: compare the compiled size with the retail function size
  (from the nonmatchings `.s`), and accept a function name to check just one. *Done when* a too-short/too-long C
  function is reported as DIFF.
- [x] **0.2 Decompile helper `tools/decomp.py NAME`**: runs m2c (pip `m2c`) on the function's nonmatchings `.s` with a
  context file built from `include/`, writes a draft to stdout. *Done when* it produces compilable C for a 10-function
  sample. (Done: `tools/decomp.py NAME [--check] [--write]`.)
- [ ] **0.3 Permuter** (`decomp-permuter`, as T1's `tools/permute.py`): sets up a function directory (base.c, target.o,
  compile.sh with our gcc 2.8.1 + maspsx 2.79 pipeline). *Done when* it runs on `f_TestAppleCollectedBit`.
- [x] **0.4 Batch check `tools/sweep.py`**: tries every C draft in a folder against its target and moves the matching
  ones into `src/`. *Done when* it can install a match unattended and the build stays OK. (Done: `tools/sweep.py --install`; first run on
  MAIN functions <= 0x100 bytes: 44 / 1096 drafts matched as they came out, 39 installed; 1 skipped for an extern
  type clash, 4 left out because the linked build differed, probably new rodata.)
- [ ] **0.5 Version checking for EU/ES**: `tools/build.py --version eu` with the same C (`#ifdef VERSION_*` only
  where the code differs). Postponed use, but the hook exists from the start. *Done when* EU builds from the USA C for
  the two matched functions.

## Phase 1 — Psy-Q 4.4 library (859 functions, 170 KB; MAIN + boot)

- [ ] **1.1 Name every library function** from the signature hits (`tools/funcstats.py` knows object -> label offsets)
  into `config/symbol_addrs_main.txt` / `_boot.txt`. *Done when* no library function is `func_*`.
- [ ] **1.2 Headers**: Psy-Q 4.4 headers (`include/psyq`, fetched, not committed) usable from `src/`.
- [ ] **1.3 Library C**: reuse existing open Psy-Q decompilations (T1's matched library C, other projects; check each
  license, list them in THIRD_PARTY_NOTICES.md) per library: LIBAPI, LIBC2, LIBETC, LIBGPU, LIBGTE, LIBCD, LIBPAD,
  LIBCARD, LIBSPU, LIBSND, LIBPRESS. Library files go to `src/main/psyq/<lib>/` with their own splat subsegments.
  *Done when* all library functions of MAIN and boot are C (or `INCLUDE_ASM` kept on purpose for hand-written asm, e.g.
  syscall stubs) and counted apart in progress.py.

## Phase 2 — MAIN.EXE engine (1107 game functions, 402 KB)

- [ ] **2.1 Core headers** in `include/`: game-state struct at `D_800BFFC0` (USA address to confirm), actor struct
  (`f_SetActorAnimation`: +0x46, +0x79, +0x7C ...), item/event tables, task/thread system
  (`f_CloseCooperativeWorkerThread`). Grow them as functions are matched; keep field names English.
- [ ] **2.2 Small leaf functions first** (< 64 bytes, ~300 of them): setters, getters, flag tests. *Target*: 300
  functions; measures the pace (functions per session) for the estimate.
- [ ] **2.3 Split `main.c` into files** by subsystem as they become clear (sound, CD/loader, text/messages, items,
  actors, camera, render, save/card, menus). splat subsegments per file; rodata moves with its functions.
- [ ] **2.4 Subsystems in order**: loader + overlay loading (confirms load addresses), text/messages (helps the port's
  translation), items/events, actors core, rendering helpers, camera, sound glue, save/memory card, menus.
- [ ] **2.5 Remaining MAIN** functions incl. the large ones (> 1 KB) with the permuter.
- *Done when* `tools/progress.py` shows MAIN 100 %.

## Phase 3 — Small programs (168 functions, 70 KB)

Can start once 2.1 exists.
- [ ] **3.1 `boot`** (21 game functions): find how it loads MAIN.EXE.
- [ ] **3.2 `game`, `demo`, `opn`, `sop`, `crd`**: each to a `c` subsegment like main; overlay header tables as data.
- *Done when* the five overlays and boot are 100 %.

## Phase 4 — Area overlays (3884 game functions, 1.84 MB after exact dups)

- [ ] **4.1 Shared overlay code**: the functions duplicated across areas (1017 exact dups) go to one shared source
  file included by every overlay that has them (`src/common_area/*.c`); near-duplicates paired with a T1-style
  `demo_pair.py` (fuzzy twins). *Done when* every exact dup is C once and builds in all overlays.
- [ ] **4.2 Small areas**: `a0g`, `a0h`, `a0i`, `a0j` (58 left after dups).
- [ ] **4.3 Bosses / medium**: `a0b`..`a0f`, `a0a`, `a0k`, `a0l`, `a09`.
- [ ] **4.4 Big areas**: `a03`, `a02`, `a01`, `a07`, `a00`, `a04`, `a05`, `a06`, `a08` (3198 functions, 1.49 MB) —
  smallest first; A00 has the most Tomba2Edit names (~210).
- *Done when* every overlay is 100 %.

## Phase 5 — Other versions

- [ ] **5.1 EU SCES-02147** from the USA C (`config/eu`, `VERSION_SCES_02147` defines where it differs).
- [ ] **5.2 ES SCES-02687** (`config/es`).
- [ ] **5.3 Optional**: FR/DE/IT retail, JP, demos and prototypes known from Tomba2Edit, if the user provides discs.

## Phase 6 — Data formats (needed by the port; can run in parallel from Phase 2 on)

- [ ] **6.1 Container readers** in Python: `TOMBA2.IDX/DAT/IMG/SND`, IMG decompression (docs/TOMBA2EDIT.md).
- [ ] **6.2 Formats** from the matched loader code: SMST, MDAT, SCLD, BGMP, SPRT, TXTD/TXT2, ANMP family, VAB/SEQ.
- [ ] **6.3 `tools/psxemu` profile for T2** (from T1): run and trace the game for checking behaviour.
- *Done when* every DAT file of the USA disc is identified and parsed (no game data committed).

## Phase 7 — Native port (as T1's `port2/`)

Starts when MAIN is mostly C (the port needs C for the engine; asm functions can be machine-translated meanwhile as T1
did).
- [ ] **7.1 Runtime**: copy T1's `port2/runtime` (software/GL renderer, SDL, GTE/GPU/SPU shims, CD from the user's
  disc), adapt to T2's libraries (Psy-Q 4.4) and memory map.
- [ ] **7.2 Generator** (T1's `port2/tools/gen2.py` + fixes.txt approach) over our `src/` and the remaining asm.
- [ ] **7.3 First boot**: title screen headless render; then the opening, A00, save/load.
- [ ] **7.4 Platforms**: PC (Linux/Windows), Android (wasm2c arm64 path from T1), launcher.
- [ ] **7.5 Spanish**: play with the ES disc's text (or a translation patch), as T1.

## Milestones

| # | Milestone | Measure |
|---|---|---|
| M1 | Tooling ready | Phase 0 done |
| M2 | Library done | 859 library functions in C |
| M3 | MAIN 25 % | ~100 KB of MAIN game code; gives the pace for the estimate |
| M4 | MAIN 100 % + small programs | engine fully C |
| M5 | All areas | 100 % USA |
| M6 | EU + ES | 100 % on the three discs |
| M7 | Port boots | title + A00 playable on PC |

The time estimate is set at M3, from the measured pace.

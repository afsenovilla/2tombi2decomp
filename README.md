<p align="center"><img src="docs/logo.png" alt="Tombi! 2" width="350">&nbsp;<img src="docs/logo_us.png" alt="Tomba! 2: The Evil Swine Return" width="350"></p>

# Tombi! 2 / Tomba! 2: The Evil Swine Return decomp

[![Platform](https://img.shields.io/badge/platform-PlayStation-003791)](#building)
[![Compiler](https://img.shields.io/badge/compiler-GCC%202.8.1%20%2B%20maspsx-orange)](docs/COMPILER.md)
[![Matching](https://img.shields.io/badge/build-byte--identical-brightgreen)](#building)

A work-in-progress **matching decompilation** of *Tombi! 2* (*Tomba! 2: The Evil Swine Return* in North America,
*Tombi! 2: Contra los cerdiablos* in Spain), Whoopee Camp, PlayStation, 1999: the game's code rewritten as C that
compiles, with the original compiler, into exactly the machine code on the disc.

It follows the method and the tools of [Tombi-Decomp](https://github.com/afsenovilla/Tombi-Decomp), the first
game, fully matched and ported to PC and Android. A native port of the second game is the long-term goal; the
decompilation comes first and stays byte for byte.

> This repository contains no game data, executables, disc images or Sony SDK files.
> You need your own legally obtained copy of the game; the build reads it from `game/`.

## Progress

Reference version: USA, *Tomba! 2* (SCUS-94454). A function counts as done when its C compiles to exactly the
bytes of the disc; everything else is still built from the original assembly, so the whole game rebuilds
byte-identical at every step.

<!-- progress:start -->
**Whole game: 23.1 % of the code matches byte for byte** (652268 of 2827992 bytes, 3686 of 7011 functions; 2026-11-22).

| Part | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| 1. Psy-Q library (MAIN + boot) | 689 / 874 | 72308 / 174440 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 41.5 % |
| 2. MAIN.EXE engine | 654 / 1168 | 108276 / 408972 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.5 % |
| 3. boot + game/demo/opn/sop/crd | 94 / 153 | 25352 / 70648 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 35.9 % |
| 4a. small areas a0g-a0j | 132 / 158 | 38576 / 61632 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 62.6 % |
| 4b. medium areas + bosses | 563 / 1020 | 152616 / 502332 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 30.4 % |
| 4c. big areas a00-a08 | 1554 / 3638 | 255140 / 1609968 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 15.8 % |

<details>
<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>

| Program | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| SCUS_944.54: boot | 8 / 13 | 876 / 3300 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.5 % |
| MAIN.EXE: engine | 654 / 1168 | 108276 / 408972 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.5 % |
| GAME.BIN | 20 / 33 | 2876 / 11236 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 25.6 % |
| DEMO.BIN | 8 / 15 | 1384 / 5152 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.9 % |
| OPN.BIN: opening | 9 / 16 | 2308 / 12860 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.9 % |
| SOP.BIN | 22 / 41 | 4424 / 14328 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 30.9 % |
| CRD.BIN: credits | 27 / 35 | 13484 / 23772 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.7 % |
| A00.BIN: area overlay | 216 / 511 | 39692 / 247424 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 16.0 % |
| A01.BIN: area overlay | 196 / 406 | 34520 / 173892 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 19.9 % |
| A02.BIN: area overlay | 141 / 306 | 20948 / 122524 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.1 % |
| A03.BIN: area overlay | 11 / 43 | 1144 / 35128 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.3 % |
| A04.BIN: area overlay | 188 / 474 | 34828 / 218464 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 15.9 % |
| A05.BIN: area overlay | 192 / 470 | 30068 / 200480 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 15.0 % |
| A06.BIN: area overlay | 213 / 519 | 34792 / 227456 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 15.3 % |
| A07.BIN: area overlay | 151 / 373 | 20956 / 159552 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 13.1 % |
| A08.BIN: area overlay | 246 / 536 | 38192 / 225048 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.0 % |
| A09.BIN: area overlay | 26 / 51 | 5924 / 20364 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 29.1 % |
| A0A.BIN: area overlay | 73 / 133 | 21636 / 64328 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 33.6 % |
| A0B.BIN: area overlay | 59 / 107 | 20772 / 61368 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 33.8 % |
| A0C.BIN: area overlay | 71 / 121 | 22448 / 63832 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 35.2 % |
| A0D.BIN: area overlay | 61 / 106 | 19600 / 57812 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 33.9 % |
| A0E.BIN: area overlay | 69 / 114 | 21260 / 60716 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 35.0 % |
| A0F.BIN: area overlay | 83 / 140 | 22976 / 71340 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 32.2 % |
| A0G.BIN: area overlay | 28 / 38 | 8860 / 16684 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 53.1 % |
| A0H.BIN: area overlay | 31 / 35 | 9624 / 13488 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 71.4 % |
| A0I.BIN: area overlay | 27 / 33 | 8760 / 14624 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 59.9 % |
| A0J.BIN: area overlay | 46 / 52 | 11332 / 16836 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 67.3 % |
| A0K.BIN: area overlay | 57 / 139 | 7472 / 61688 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.1 % |
| A0L.BIN: area overlay | 64 / 109 | 10528 / 40884 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 25.8 % |

</details>
<!-- progress:end -->

The library part is Sony's Psy-Q 4.4 code linked into the game (`src/<prog>/psyq/`), counted together with the
library functions kept as assembly on purpose (they were written in assembly). Updated with
`python3 -I tools/readme_progress.py`.

## Releases

| Release | Serial | Status |
|---|---|---|
| USA, *Tomba! 2: The Evil Swine Return* (reference) | SCUS-94454 | all 29 programs rebuild byte-identical; C in progress (above) |
| Europe, *Tombi! 2* | SCES-02147 | all 29 programs rebuild byte-identical (`--version eu`); ~96 % of the USA functions found in it |
| Spain, *Tombi! 2: Contra los cerdiablos* | SCES-02687 | ~96 % of the USA functions found in it |

The 29 programs: the boot executable, `MAIN.EXE` (the engine), the area overlays `A00`..`A0L` and the `GAME`,
`DEMO`, `OPN`, `SOP` and `CRD` overlays ([docs/DISCS.md](docs/DISCS.md)).

## Building

```bash
bash tools/session_bootstrap.sh
```

or by hand: install `binutils-mipsel-linux-gnu`, `pip install -r tools/requirements.txt` and
`pip install --no-deps splat64==0.35.2`, put the disc's files in `game/usa/` (`bash tools/disc_fetch.sh USA` with
`GAME_FILES_URL_T2_USA` set to a link to your copy), then

```bash
python3 tools/build.py
```

Every program prints `OK` when its rebuilt file is byte-identical to the original.

## How the work is done

- `tools/build.py`: splat split, C compiled with the game's compiler (GCC 2.8.1 + ASPSX 2.79 through maspsx),
  link, SHA-1 compared with the disc's file. C `switch` statements reuse the disc's jump tables (`tools/jtbl.py`).
- `tools/ccheck.py`: compile one scratch C file and compare each function with the retail bytes (`--sbs`, or
  `tools/sbs.py`: side-by-side diff of ours and retail); `tools/install_c.py` puts matched functions in place
  (linked-build checked, symbols renamed to the program's names from the relocations).
- `tools/sweep.py` (m2c drafts that match as they are; m2c gets the jump tables), `tools/hillclimb.py` (small
  source transforms that bring drafts closer), `tools/permute.py` (decomp-permuter), `tools/permlines.py`
  (statement-order search over lines marked `//P`), `tools/variants.py` (several variants of one function in a file),
  `tools/magicdiv.py` (the divisor behind a magic-number multiply).
- `tools/dupsweep.py`: the area overlays share many functions; one matched copy is installed in every other copy,
  also when they differ only in constants. `tools/nearcopy.py` does the same for near copies (a few differing
  words, patched constants and offsets) and lists the closest C for hand matching.
- `tools/libsweep.py` and friends: the Psy-Q library, by signature.

## Documents

- [docs/ROADMAP.md](docs/ROADMAP.md): the phases, step by step.
- [docs/STATUS.md](docs/STATUS.md): current state, recipes for hand matching, next steps.
- [docs/DISCS.md](docs/DISCS.md): the three discs, executables, overlays, load addresses, library version.
- [docs/COMPILER.md](docs/COMPILER.md): how the compiler was identified.
- [docs/TOMBA2EDIT.md](docs/TOMBA2EDIT.md): what [Tomba2Edit](https://github.com/SiergiejW/Tomba2Edit) contributed
  (names, formats).
- [docs/PLAN.md](docs/PLAN.md): function counts and the order of work.

## Thanks

[Tomba2Edit](https://github.com/SiergiejW/Tomba2Edit) by SiergiejW for the function names and file formats;
[splat](https://github.com/ethteck/splat), [maspsx](https://github.com/mkst/maspsx),
[m2c](https://github.com/matt-kempster/m2c) and [decomp-permuter](https://github.com/simonlindholm/decomp-permuter).
See [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).

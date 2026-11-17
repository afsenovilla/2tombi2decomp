<!-- logo: <p align="center"><img src="docs/logo.png" alt="Tomba! 2" width="400"></p> -->

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
**Whole game: 4.8 % of the code matches byte for byte** (135604 of 2827992 bytes, 1543 of 7011 functions; 2026-11-17).

| Part | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| 1. Psy-Q library (MAIN + boot) | 393 / 867 | 24892 / 169632 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 14.7 % |
| 2. MAIN.EXE engine | 430 / 1167 | 40208 / 408928 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 9.8 % |
| 3. boot + game/demo/opn/sop/crd | 9 / 161 | 900 / 75500 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 1.2 % |
| 4a. small areas a0g-a0j | 47 / 158 | 4820 / 61632 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 7.8 % |
| 4b. medium areas + bosses | 165 / 1020 | 15564 / 502332 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.1 % |
| 4c. big areas a00-a08 | 499 / 3638 | 49220 / 1609968 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.1 % |

<details>
<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>

| Program | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| SCUS_944.54: boot | 2 / 21 | 180 / 8152 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 2.2 % |
| MAIN.EXE: engine | 430 / 1167 | 40208 / 408928 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 9.8 % |
| GAME.BIN | 3 / 33 | 152 / 11236 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 1.4 % |
| DEMO.BIN | 0 / 15 | 0 / 5152 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 0.0 % |
| OPN.BIN: opening | 0 / 16 | 0 / 12860 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 0.0 % |
| SOP.BIN | 4 / 41 | 568 / 14328 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 4.0 % |
| CRD.BIN: credits | 0 / 35 | 0 / 23772 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 0.0 % |
| A00.BIN: area overlay | 53 / 511 | 6416 / 247424 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 2.6 % |
| A01.BIN: area overlay | 41 / 406 | 4492 / 173892 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 2.6 % |
| A02.BIN: area overlay | 56 / 306 | 5336 / 122524 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 4.4 % |
| A03.BIN: area overlay | 7 / 43 | 452 / 35128 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 1.3 % |
| A04.BIN: area overlay | 68 / 474 | 8780 / 218464 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 4.0 % |
| A05.BIN: area overlay | 58 / 470 | 5532 / 200480 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 2.8 % |
| A06.BIN: area overlay | 74 / 519 | 6972 / 227456 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.1 % |
| A07.BIN: area overlay | 59 / 373 | 4076 / 159552 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 2.6 % |
| A08.BIN: area overlay | 83 / 536 | 7164 / 225048 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.2 % |
| A09.BIN: area overlay | 3 / 51 | 244 / 20364 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 1.2 % |
| A0A.BIN: area overlay | 20 / 133 | 1848 / 64328 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 2.9 % |
| A0B.BIN: area overlay | 15 / 107 | 1632 / 61368 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 2.7 % |
| A0C.BIN: area overlay | 20 / 121 | 2348 / 63832 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.7 % |
| A0D.BIN: area overlay | 16 / 106 | 1764 / 57812 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.1 % |
| A0E.BIN: area overlay | 22 / 114 | 2112 / 60716 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.5 % |
| A0F.BIN: area overlay | 23 / 140 | 2292 / 71340 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.2 % |
| A0G.BIN: area overlay | 10 / 38 | 1168 / 16684 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 7.0 % |
| A0H.BIN: area overlay | 11 / 35 | 1292 / 13488 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 9.6 % |
| A0I.BIN: area overlay | 9 / 33 | 996 / 14624 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 6.8 % |
| A0J.BIN: area overlay | 17 / 52 | 1364 / 16836 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 8.1 % |
| A0K.BIN: area overlay | 22 / 139 | 2240 / 61688 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.6 % |
| A0L.BIN: area overlay | 24 / 109 | 1084 / 40884 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 2.7 % |

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
- `tools/ccheck.py`: compile one scratch C file and compare each function with the retail bytes;
  `tools/install_c.py` puts matched functions in place (linked-build checked).
- `tools/sweep.py` (m2c drafts that match as they are), `tools/hillclimb.py` (small source transforms that bring
  drafts closer), `tools/permute.py` (decomp-permuter).
- `tools/dupsweep.py`: the area overlays share many functions; one matched copy is installed in every other copy,
  also when they differ only in constants.
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

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
**Whole game: 33.1 % of the code matches byte for byte** (936888 of 2827992 bytes, 4220 of 7011 functions; 2026-11-23).

| Part | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| 1. Psy-Q library (MAIN + boot) | 756 / 873 | 98136 / 174272 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.3 % |
| 2. MAIN.EXE engine | 737 / 1169 | 148392 / 409140 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 36.3 % |
| 3. boot + game/demo/opn/sop/crd | 106 / 153 | 31480 / 70648 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.6 % |
| 4a. small areas a0g-a0j | 138 / 158 | 44216 / 61632 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 71.7 % |
| 4b. medium areas + bosses | 678 / 1020 | 216004 / 502332 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 43.0 % |
| 4c. big areas a00-a08 | 1805 / 3638 | 398660 / 1609968 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 24.8 % |

<details>
<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>

| Program | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| SCUS_944.54: boot | 8 / 13 | 876 / 3300 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.5 % |
| MAIN.EXE: engine | 737 / 1169 | 148392 / 409140 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 36.3 % |
| GAME.BIN | 27 / 33 | 6384 / 11236 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.8 % |
| DEMO.BIN | 9 / 15 | 2268 / 5152 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.0 % |
| OPN.BIN: opening | 9 / 16 | 2308 / 12860 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.9 % |
| SOP.BIN | 26 / 41 | 6160 / 14328 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 43.0 % |
| CRD.BIN: credits | 27 / 35 | 13484 / 23772 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.7 % |
| A00.BIN: area overlay | 259 / 511 | 66376 / 247424 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.8 % |
| A01.BIN: area overlay | 234 / 406 | 56952 / 173892 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 32.8 % |
| A02.BIN: area overlay | 180 / 306 | 41324 / 122524 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 33.7 % |
| A03.BIN: area overlay | 12 / 43 | 1868 / 35128 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 5.3 % |
| A04.BIN: area overlay | 213 / 474 | 48328 / 218464 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 22.1 % |
| A05.BIN: area overlay | 215 / 470 | 43876 / 200480 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 21.9 % |
| A06.BIN: area overlay | 244 / 519 | 53624 / 227456 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 23.6 % |
| A07.BIN: area overlay | 178 / 373 | 33400 / 159552 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 20.9 % |
| A08.BIN: area overlay | 270 / 536 | 52912 / 225048 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 23.5 % |
| A09.BIN: area overlay | 32 / 51 | 8128 / 20364 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 39.9 % |
| A0A.BIN: area overlay | 88 / 133 | 29200 / 64328 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 45.4 % |
| A0B.BIN: area overlay | 69 / 107 | 27072 / 61368 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.1 % |
| A0C.BIN: area overlay | 82 / 121 | 28504 / 63832 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.7 % |
| A0D.BIN: area overlay | 73 / 106 | 25528 / 57812 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.2 % |
| A0E.BIN: area overlay | 81 / 114 | 27172 / 60716 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.8 % |
| A0F.BIN: area overlay | 96 / 140 | 30072 / 71340 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 42.2 % |
| A0G.BIN: area overlay | 29 / 38 | 9924 / 16684 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 59.5 % |
| A0H.BIN: area overlay | 32 / 35 | 10688 / 13488 | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 79.2 % |
| A0I.BIN: area overlay | 29 / 33 | 10272 / 14624 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 70.2 % |
| A0J.BIN: area overlay | 48 / 52 | 13332 / 16836 | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 79.2 % |
| A0K.BIN: area overlay | 78 / 139 | 19008 / 61688 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 30.8 % |
| A0L.BIN: area overlay | 79 / 109 | 21320 / 40884 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 52.1 % |

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

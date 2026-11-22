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
**Whole game: 15.2 % of the code matches byte for byte** (429912 of 2827992 bytes, 3029 of 7011 functions; 2026-11-22).

| Part | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| 1. Psy-Q library (MAIN + boot) | 607 / 865 | 53004 / 169544 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 31.3 % |
| 2. MAIN.EXE engine | 548 / 1168 | 77824 / 408972 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 19.0 % |
| 3. boot + game/demo/opn/sop/crd | 90 / 162 | 22980 / 75544 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 30.4 % |
| 4a. small areas a0g-a0j | 102 / 158 | 19028 / 61632 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 30.9 % |
| 4b. medium areas + bosses | 439 / 1020 | 85004 / 502332 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 16.9 % |
| 4c. big areas a00-a08 | 1243 / 3638 | 172072 / 1609968 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 10.7 % |

<details>
<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>

| Program | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| SCUS_944.54: boot | 9 / 22 | 1024 / 8196 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.5 % |
| MAIN.EXE: engine | 548 / 1168 | 77824 / 408972 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 19.0 % |
| GAME.BIN | 18 / 33 | 2364 / 11236 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 21.0 % |
| DEMO.BIN | 8 / 15 | 1384 / 5152 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.9 % |
| OPN.BIN: opening | 9 / 16 | 2308 / 12860 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.9 % |
| SOP.BIN | 20 / 41 | 2844 / 14328 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 19.8 % |
| CRD.BIN: credits | 26 / 35 | 13056 / 23772 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 54.9 % |
| A00.BIN: area overlay | 166 / 511 | 24748 / 247424 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 10.0 % |
| A01.BIN: area overlay | 152 / 406 | 22392 / 173892 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.9 % |
| A02.BIN: area overlay | 117 / 306 | 13988 / 122524 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 11.4 % |
| A03.BIN: area overlay | 10 / 43 | 940 / 35128 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 2.7 % |
| A04.BIN: area overlay | 149 / 474 | 23160 / 218464 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 10.6 % |
| A05.BIN: area overlay | 154 / 470 | 21632 / 200480 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 10.8 % |
| A06.BIN: area overlay | 169 / 519 | 23600 / 227456 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 10.4 % |
| A07.BIN: area overlay | 127 / 373 | 14412 / 159552 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 9.0 % |
| A08.BIN: area overlay | 199 / 536 | 27200 / 225048 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.1 % |
| A09.BIN: area overlay | 24 / 51 | 5408 / 20364 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.6 % |
| A0A.BIN: area overlay | 56 / 133 | 12008 / 64328 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 18.7 % |
| A0B.BIN: area overlay | 42 / 107 | 10088 / 61368 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 16.4 % |
| A0C.BIN: area overlay | 50 / 121 | 11068 / 63832 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.3 % |
| A0D.BIN: area overlay | 46 / 106 | 10500 / 57812 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 18.2 % |
| A0E.BIN: area overlay | 51 / 114 | 10856 / 60716 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.9 % |
| A0F.BIN: area overlay | 64 / 140 | 12472 / 71340 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.5 % |
| A0G.BIN: area overlay | 20 / 38 | 3784 / 16684 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 22.7 % |
| A0H.BIN: area overlay | 23 / 35 | 4604 / 13488 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 34.1 % |
| A0I.BIN: area overlay | 19 / 33 | 3740 / 14624 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 25.6 % |
| A0J.BIN: area overlay | 40 / 52 | 6900 / 16836 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 41.0 % |
| A0K.BIN: area overlay | 55 / 139 | 7208 / 61688 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 11.7 % |
| A0L.BIN: area overlay | 51 / 109 | 5396 / 40884 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 13.2 % |

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

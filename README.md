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
**Whole game: 61.2 % of the code matches byte for byte** (1731564 of 2827992 bytes, 5367 of 7011 functions; 2026-11-28).

| Part | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| 1. Psy-Q library (MAIN + boot) | 756 / 873 | 98136 / 174272 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.3 % |
| 2. MAIN.EXE engine | 949 / 1169 | 262632 / 409140 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 64.2 % |
| 3. boot + game/demo/opn/sop/crd | 127 / 153 | 49120 / 70648 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 69.5 % |
| 4a. small areas a0g-a0j | 151 / 158 | 58040 / 61632 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩⬜ 94.2 % |
| 4b. medium areas + bosses | 865 / 1020 | 376420 / 502332 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 74.9 % |
| 4c. big areas a00-a08 | 2519 / 3638 | 887216 / 1609968 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 55.1 % |

<details>
<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>

| Program | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| SCUS_944.54: boot | 8 / 13 | 876 / 3300 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.5 % |
| MAIN.EXE: engine | 949 / 1169 | 262632 / 409140 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 64.2 % |
| GAME.BIN | 28 / 33 | 6636 / 11236 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 59.1 % |
| DEMO.BIN | 10 / 15 | 2672 / 5152 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 51.9 % |
| OPN.BIN: opening | 13 / 16 | 9568 / 12860 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 74.4 % |
| SOP.BIN | 39 / 41 | 13552 / 14328 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩⬜ 94.6 % |
| CRD.BIN: credits | 29 / 35 | 15816 / 23772 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 66.5 % |
| A00.BIN: area overlay | 370 / 511 | 147112 / 247424 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 59.5 % |
| A01.BIN: area overlay | 316 / 406 | 120656 / 173892 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 69.4 % |
| A02.BIN: area overlay | 291 / 306 | 111012 / 122524 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩⬜ 90.6 % |
| A03.BIN: area overlay | 37 / 43 | 21568 / 35128 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 61.4 % |
| A04.BIN: area overlay | 286 / 474 | 96812 / 218464 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.3 % |
| A05.BIN: area overlay | 284 / 470 | 88960 / 200480 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.4 % |
| A06.BIN: area overlay | 314 / 519 | 100356 / 227456 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.1 % |
| A07.BIN: area overlay | 259 / 373 | 82528 / 159552 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 51.7 % |
| A08.BIN: area overlay | 362 / 536 | 118212 / 225048 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 52.5 % |
| A09.BIN: area overlay | 42 / 51 | 14044 / 20364 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 69.0 % |
| A0A.BIN: area overlay | 113 / 133 | 50152 / 64328 | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 78.0 % |
| A0B.BIN: area overlay | 89 / 107 | 47204 / 61368 | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 76.9 % |
| A0C.BIN: area overlay | 105 / 121 | 50792 / 63832 | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 79.6 % |
| A0D.BIN: area overlay | 97 / 106 | 47152 / 57812 | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 81.6 % |
| A0E.BIN: area overlay | 97 / 114 | 45068 / 60716 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 74.2 % |
| A0F.BIN: area overlay | 122 / 140 | 54192 / 71340 | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 76.0 % |
| A0G.BIN: area overlay | 32 / 38 | 13464 / 16684 | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 80.7 % |
| A0H.BIN: area overlay | 35 / 35 | 13488 / 13488 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 100.0 % |
| A0I.BIN: area overlay | 33 / 33 | 14624 / 14624 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 100.0 % |
| A0J.BIN: area overlay | 51 / 52 | 16464 / 16836 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 97.8 % |
| A0K.BIN: area overlay | 107 / 139 | 38404 / 61688 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 62.3 % |
| A0L.BIN: area overlay | 93 / 109 | 29412 / 40884 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 71.9 % |

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

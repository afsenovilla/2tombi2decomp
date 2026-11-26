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
**Whole game: 52.0 % of the code matches byte for byte** (1471468 of 2827992 bytes, 5015 of 7011 functions; 2026-11-26).

| Part | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| 1. Psy-Q library (MAIN + boot) | 756 / 873 | 98136 / 174272 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.3 % |
| 2. MAIN.EXE engine | 861 / 1169 | 199796 / 409140 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 48.8 % |
| 3. boot + game/demo/opn/sop/crd | 125 / 153 | 48268 / 70648 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 68.3 % |
| 4a. small areas a0g-a0j | 149 / 158 | 55844 / 61632 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩⬜ 90.6 % |
| 4b. medium areas + bosses | 807 / 1020 | 332672 / 502332 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 66.2 % |
| 4c. big areas a00-a08 | 2317 / 3638 | 736752 / 1609968 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 45.8 % |

<details>
<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>

| Program | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| SCUS_944.54: boot | 8 / 13 | 876 / 3300 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.5 % |
| MAIN.EXE: engine | 861 / 1169 | 199796 / 409140 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 48.8 % |
| GAME.BIN | 28 / 33 | 6636 / 11236 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 59.1 % |
| DEMO.BIN | 9 / 15 | 2268 / 5152 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.0 % |
| OPN.BIN: opening | 13 / 16 | 9568 / 12860 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 74.4 % |
| SOP.BIN | 38 / 41 | 13104 / 14328 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩⬜ 91.5 % |
| CRD.BIN: credits | 29 / 35 | 15816 / 23772 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 66.5 % |
| A00.BIN: area overlay | 341 / 511 | 125104 / 247424 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 50.6 % |
| A01.BIN: area overlay | 280 / 406 | 91564 / 173892 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 52.7 % |
| A02.BIN: area overlay | 275 / 306 | 93300 / 122524 | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 76.1 % |
| A03.BIN: area overlay | 34 / 43 | 15496 / 35128 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.1 % |
| A04.BIN: area overlay | 262 / 474 | 81544 / 218464 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 37.3 % |
| A05.BIN: area overlay | 265 / 470 | 76864 / 200480 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 38.3 % |
| A06.BIN: area overlay | 288 / 519 | 84060 / 227456 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 37.0 % |
| A07.BIN: area overlay | 240 / 373 | 68780 / 159552 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 43.1 % |
| A08.BIN: area overlay | 332 / 536 | 100040 / 225048 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.5 % |
| A09.BIN: area overlay | 38 / 51 | 12496 / 20364 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 61.4 % |
| A0A.BIN: area overlay | 105 / 133 | 44564 / 64328 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 69.3 % |
| A0B.BIN: area overlay | 80 / 107 | 39452 / 61368 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 64.3 % |
| A0C.BIN: area overlay | 101 / 121 | 46404 / 63832 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 72.7 % |
| A0D.BIN: area overlay | 86 / 106 | 39484 / 57812 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 68.3 % |
| A0E.BIN: area overlay | 92 / 114 | 40848 / 60716 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 67.3 % |
| A0F.BIN: area overlay | 113 / 140 | 46352 / 71340 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 65.0 % |
| A0G.BIN: area overlay | 30 / 38 | 11268 / 16684 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 67.5 % |
| A0H.BIN: area overlay | 35 / 35 | 13488 / 13488 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 100.0 % |
| A0I.BIN: area overlay | 33 / 33 | 14624 / 14624 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 100.0 % |
| A0J.BIN: area overlay | 51 / 52 | 16464 / 16836 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 97.8 % |
| A0K.BIN: area overlay | 103 / 139 | 36220 / 61688 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 58.7 % |
| A0L.BIN: area overlay | 89 / 109 | 26852 / 40884 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 65.7 % |

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

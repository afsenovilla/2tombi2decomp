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
**Whole game: 18.2 % of the code matches byte for byte** (514952 of 2827992 bytes, 3396 of 7011 functions; 2026-11-22).

| Part | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| 1. Psy-Q library (MAIN + boot) | 660 / 865 | 65244 / 169544 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 38.5 % |
| 2. MAIN.EXE engine | 599 / 1168 | 87784 / 408972 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 21.5 % |
| 3. boot + game/demo/opn/sop/crd | 93 / 162 | 23920 / 75544 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 31.7 % |
| 4a. small areas a0g-a0j | 112 / 158 | 23032 / 61632 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 37.4 % |
| 4b. medium areas + bosses | 508 / 1020 | 110104 / 502332 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 21.9 % |
| 4c. big areas a00-a08 | 1424 / 3638 | 204868 / 1609968 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.7 % |

<details>
<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>

| Program | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| SCUS_944.54: boot | 9 / 22 | 1024 / 8196 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.5 % |
| MAIN.EXE: engine | 599 / 1168 | 87784 / 408972 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 21.5 % |
| GAME.BIN | 20 / 33 | 2876 / 11236 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 25.6 % |
| DEMO.BIN | 8 / 15 | 1384 / 5152 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.9 % |
| OPN.BIN: opening | 9 / 16 | 2308 / 12860 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.9 % |
| SOP.BIN | 20 / 41 | 2844 / 14328 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 19.8 % |
| CRD.BIN: credits | 27 / 35 | 13484 / 23772 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.7 % |
| A00.BIN: area overlay | 193 / 511 | 31200 / 247424 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.6 % |
| A01.BIN: area overlay | 173 / 406 | 26948 / 173892 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 15.5 % |
| A02.BIN: area overlay | 129 / 306 | 16540 / 122524 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 13.5 % |
| A03.BIN: area overlay | 11 / 43 | 1144 / 35128 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 3.3 % |
| A04.BIN: area overlay | 171 / 474 | 26644 / 218464 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.2 % |
| A05.BIN: area overlay | 181 / 470 | 25628 / 200480 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.8 % |
| A06.BIN: area overlay | 197 / 519 | 28372 / 227456 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.5 % |
| A07.BIN: area overlay | 140 / 373 | 16400 / 159552 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 10.3 % |
| A08.BIN: area overlay | 229 / 536 | 31992 / 225048 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 14.2 % |
| A09.BIN: area overlay | 26 / 51 | 5924 / 20364 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 29.1 % |
| A0A.BIN: area overlay | 66 / 133 | 15880 / 64328 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 24.7 % |
| A0B.BIN: area overlay | 49 / 107 | 13204 / 61368 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 21.5 % |
| A0C.BIN: area overlay | 61 / 121 | 14784 / 63832 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 23.2 % |
| A0D.BIN: area overlay | 54 / 106 | 13888 / 57812 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 24.0 % |
| A0E.BIN: area overlay | 60 / 114 | 14292 / 60716 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 23.5 % |
| A0F.BIN: area overlay | 74 / 140 | 16364 / 71340 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 22.9 % |
| A0G.BIN: area overlay | 23 / 38 | 4936 / 16684 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 29.6 % |
| A0H.BIN: area overlay | 26 / 35 | 5756 / 13488 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 42.7 % |
| A0I.BIN: area overlay | 22 / 33 | 4892 / 14624 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 33.5 % |
| A0J.BIN: area overlay | 41 / 52 | 7448 / 16836 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.2 % |
| A0K.BIN: area overlay | 57 / 139 | 7472 / 61688 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.1 % |
| A0L.BIN: area overlay | 61 / 109 | 8296 / 40884 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 20.3 % |

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

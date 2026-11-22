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
**Whole game: 8.8 % of the code matches byte for byte** (248948 of 2827992 bytes, 2296 of 7011 functions; 2026-11-22).

| Part | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| 1. Psy-Q library (MAIN + boot) | 393 / 867 | 24892 / 169632 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 14.7 % |
| 2. MAIN.EXE engine | 506 / 1167 | 57896 / 408928 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 14.2 % |
| 3. boot + game/demo/opn/sop/crd | 53 / 161 | 7124 / 75500 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 9.4 % |
| 4a. small areas a0g-a0j | 63 / 158 | 8748 / 61632 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 14.2 % |
| 4b. medium areas + bosses | 354 / 1020 | 51108 / 502332 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 10.2 % |
| 4c. big areas a00-a08 | 927 / 3638 | 99180 / 1609968 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 6.2 % |

<details>
<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>

| Program | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| SCUS_944.54: boot | 8 / 21 | 980 / 8152 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.0 % |
| MAIN.EXE: engine | 506 / 1167 | 57896 / 408928 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 14.2 % |
| GAME.BIN | 15 / 33 | 1764 / 11236 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 15.7 % |
| DEMO.BIN | 6 / 15 | 928 / 5152 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 18.0 % |
| OPN.BIN: opening | 4 / 16 | 596 / 12860 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 4.6 % |
| SOP.BIN | 19 / 41 | 2588 / 14328 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 18.1 % |
| CRD.BIN: credits | 1 / 35 | 268 / 23772 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 1.1 % |
| A00.BIN: area overlay | 113 / 511 | 13988 / 247424 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 5.7 % |
| A01.BIN: area overlay | 94 / 406 | 10872 / 173892 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 6.3 % |
| A02.BIN: area overlay | 83 / 306 | 8524 / 122524 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 7.0 % |
| A03.BIN: area overlay | 7 / 43 | 452 / 35128 | ⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 1.3 % |
| A04.BIN: area overlay | 119 / 474 | 15000 / 218464 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 6.9 % |
| A05.BIN: area overlay | 116 / 470 | 12420 / 200480 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 6.2 % |
| A06.BIN: area overlay | 137 / 519 | 14024 / 227456 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 6.2 % |
| A07.BIN: area overlay | 106 / 373 | 9224 / 159552 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 5.8 % |
| A08.BIN: area overlay | 152 / 536 | 14676 / 225048 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 6.5 % |
| A09.BIN: area overlay | 17 / 51 | 2788 / 20364 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 13.7 % |
| A0A.BIN: area overlay | 53 / 133 | 10772 / 64328 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 16.7 % |
| A0B.BIN: area overlay | 29 / 107 | 4708 / 61368 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 7.7 % |
| A0C.BIN: area overlay | 33 / 121 | 4496 / 63832 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 7.0 % |
| A0D.BIN: area overlay | 33 / 106 | 5120 / 57812 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 8.9 % |
| A0E.BIN: area overlay | 37 / 114 | 5244 / 60716 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 8.6 % |
| A0F.BIN: area overlay | 48 / 140 | 6020 / 71340 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 8.4 % |
| A0G.BIN: area overlay | 13 / 38 | 1956 / 16684 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 11.7 % |
| A0H.BIN: area overlay | 15 / 35 | 2324 / 13488 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 17.2 % |
| A0I.BIN: area overlay | 12 / 33 | 1784 / 14624 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 12.2 % |
| A0J.BIN: area overlay | 23 / 52 | 2684 / 16836 | 🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜ 15.9 % |
| A0K.BIN: area overlay | 55 / 139 | 7208 / 61688 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 11.7 % |
| A0L.BIN: area overlay | 49 / 109 | 4752 / 40884 | 🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜ 11.6 % |

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

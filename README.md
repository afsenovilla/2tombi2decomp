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
**Whole game: 49.3 % of the code matches byte for byte** (1395488 of 2827992 bytes, 4926 of 7011 functions; 2026-11-26).

| Part | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| 1. Psy-Q library (MAIN + boot) | 756 / 873 | 98136 / 174272 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.3 % |
| 2. MAIN.EXE engine | 846 / 1169 | 190684 / 409140 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 46.6 % |
| 3. boot + game/demo/opn/sop/crd | 125 / 153 | 48268 / 70648 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 68.3 % |
| 4a. small areas a0g-a0j | 149 / 158 | 55844 / 61632 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩⬜ 90.6 % |
| 4b. medium areas + bosses | 775 / 1020 | 295340 / 502332 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 58.8 % |
| 4c. big areas a00-a08 | 2275 / 3638 | 707216 / 1609968 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 43.9 % |

<details>
<summary><b>Per program</b> (game code, without the Psy-Q library)</summary>

| Program | Functions | Bytes | Matching (bytes) |
|---|---:|---:|---|
| SCUS_944.54: boot | 8 / 13 | 876 / 3300 | 🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜ 26.5 % |
| MAIN.EXE: engine | 846 / 1169 | 190684 / 409140 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 46.6 % |
| GAME.BIN | 28 / 33 | 6636 / 11236 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 59.1 % |
| DEMO.BIN | 9 / 15 | 2268 / 5152 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 44.0 % |
| OPN.BIN: opening | 13 / 16 | 9568 / 12860 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 74.4 % |
| SOP.BIN | 38 / 41 | 13104 / 14328 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩⬜ 91.5 % |
| CRD.BIN: credits | 29 / 35 | 15816 / 23772 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 66.5 % |
| A00.BIN: area overlay | 328 / 511 | 118836 / 247424 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 48.0 % |
| A01.BIN: area overlay | 279 / 406 | 91168 / 173892 | 🟩🟩🟩🟩🟩⬜⬜⬜⬜⬜ 52.4 % |
| A02.BIN: area overlay | 271 / 306 | 90632 / 122524 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 74.0 % |
| A03.BIN: area overlay | 31 / 43 | 13164 / 35128 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 37.5 % |
| A04.BIN: area overlay | 259 / 474 | 78288 / 218464 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 35.8 % |
| A05.BIN: area overlay | 264 / 470 | 76368 / 200480 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 38.1 % |
| A06.BIN: area overlay | 287 / 519 | 83604 / 227456 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 36.8 % |
| A07.BIN: area overlay | 238 / 373 | 67508 / 159552 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 42.3 % |
| A08.BIN: area overlay | 318 / 536 | 87648 / 225048 | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 38.9 % |
| A09.BIN: area overlay | 36 / 51 | 11492 / 20364 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.4 % |
| A0A.BIN: area overlay | 101 / 133 | 38876 / 64328 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 60.4 % |
| A0B.BIN: area overlay | 77 / 107 | 34476 / 61368 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 56.2 % |
| A0C.BIN: area overlay | 94 / 121 | 38712 / 63832 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 60.6 % |
| A0D.BIN: area overlay | 83 / 106 | 34948 / 57812 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 60.5 % |
| A0E.BIN: area overlay | 88 / 114 | 35032 / 60716 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 57.7 % |
| A0F.BIN: area overlay | 110 / 140 | 41248 / 71340 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 57.8 % |
| A0G.BIN: area overlay | 30 / 38 | 11268 / 16684 | 🟩🟩🟩🟩🟩🟩🟩⬜⬜⬜ 67.5 % |
| A0H.BIN: area overlay | 35 / 35 | 13488 / 13488 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 100.0 % |
| A0I.BIN: area overlay | 33 / 33 | 14624 / 14624 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 100.0 % |
| A0J.BIN: area overlay | 51 / 52 | 16464 / 16836 | 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 97.8 % |
| A0K.BIN: area overlay | 98 / 139 | 34116 / 61688 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 55.3 % |
| A0L.BIN: area overlay | 88 / 109 | 26440 / 40884 | 🟩🟩🟩🟩🟩🟩⬜⬜⬜⬜ 64.7 % |

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

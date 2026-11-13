# 2tombi2decomp

A work-in-progress matching decompilation of **Tombi! 2** / **Tomba! 2: The Evil Swine Return** (Whoopee Camp, PS1,
1999), following the method of [Tombi-Decomp](https://github.com/afsenovilla/Tombi-Decomp) (the first game, 100 %
matched, plus a native PC/Android port). A native port of the second game is the long-term goal.

This repository contains **no game data**. You need your own copy of the game; the build reads it from `game/`.

| Release | Serial | Status |
|---|---|---|
| USA, *The Evil Swine Return* (reference) | SCUS-94454 | all 29 programs rebuild byte-identical from disassembly; first C functions matched |
| Europe | SCES-02147 | all 29 programs rebuild byte-identical (`--version eu`); ~96 % of the USA functions found (masked) |
| Spain, *Contra los cerdiablos* | SCES-02687 | separate build, ~96 % of the USA functions found (masked) |

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

## Documents

- [docs/DISCS.md](docs/DISCS.md): the three discs, executables, overlays, containers, library version.
- [docs/PLAN.md](docs/PLAN.md): function counts and the order of work.
- [docs/STATUS.md](docs/STATUS.md): current state and next steps.

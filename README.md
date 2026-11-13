# 2tombi2decomp

A work-in-progress matching decompilation of **Tombi! 2** / **Tomba! 2: The Evil Swine Return** (Whoopee Camp, PS1,
1999), following the method of [Tombi-Decomp](https://github.com/afsenovilla/Tombi-Decomp) (the first game, 100 %
matched, plus a native PC/Android port). A native port of the second game is the long-term goal.

This repository contains **no game data**. You need your own copy of the game; the build reads it from `game/`.

| Release | Serial | Status |
|---|---|---|
| Europe (reference) | SCES-02147 | all 29 programs rebuild byte-identical from disassembly; C decompilation not started |
| Spain, *Contra los cerdiablos* | SCES-02687 | separate build, ~98 % of the EU functions found (masked) |
| USA, *The Evil Swine Return* | SCUS-94454 | separate build, ~96 % of the EU functions found (masked) |

## Building

```bash
bash tools/session_bootstrap.sh
```

or by hand: install `binutils-mipsel-linux-gnu`, `pip install -r tools/requirements.txt` and
`pip install --no-deps splat64==0.35.2`, put the disc's files in `game/eu/` (`bash tools/disc_fetch.sh EU` with
`GAME_FILES_URL_T2_EU` set to a link to your copy), then

```bash
python3 tools/build.py
```

Every program prints `OK` when its rebuilt file is byte-identical to the original.

## Documents

- [docs/DISCS.md](docs/DISCS.md): the three discs, executables, overlays, containers, library version.
- [docs/PLAN.md](docs/PLAN.md): function counts and the order of work.
- [docs/STATUS.md](docs/STATUS.md): current state and next steps.

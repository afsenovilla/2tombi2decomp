# Working on 2tombi2decomp with Claude Code

Read this first in every session. The current state and the open tasks are in `docs/STATUS.md`; keep that file up to
date as work lands (it is the hand-off between sessions).

**First thing in a new cloud session:** run `bash tools/session_bootstrap.sh`, without being asked. It installs the
packages and the PS1 toolchain, downloads and extracts the discs from the `GAME_FILES_URL_T2_*` environment variables,
fetches the Psy-Q signatures and runs the matching build of every program (a few minutes plus the downloads). It skips
whatever is already there. If a variable is missing, tell the user to add it in the cloud environment's settings and
start a new session.

## The project

A matching decompilation of Tombi! 2 / Tomba! 2: The Evil Swine Return (PS1, 1999), and later a native port, built the
same way as the first game's project, `afsenovilla/Tombi-Decomp` (the reference: clone it read-only next to this repo
when its tools or notes are needed; copy and adapt, do not reinvent). Reference version: **USA SCUS-94454** (since 2026-11-13: Tomba2Edit and the Tomba Club research are on USA
addresses; EU SCES-02147 is kept as a second version in `config/eu/`).
Discs: docs/DISCS.md. Plan and numbers: docs/PLAN.md.

## How to talk to the user

- Reply in **Spanish**, short and direct, first person. Never claim something works without verifying it; say
  plainly what was tested and what was not.
- **Everything generated is in English**: docs, reports, agents' reports, notes, commit messages, and the labels,
  titles and captions inside generated images. Only the chat replies are in Spanish.
- Show the user what was found at each step; ask before big decisions (repo layout, reference version, tooling that
  is hard to undo).

## Hard rules

- **Never commit** game/SDK binaries, disc images, extracted assets, game graphics, text dumps, screenshots or saves.
  "Ship scripts, not pixels": everything is rebuilt from the user's disc at build/run time; tables hold addresses,
  offsets and names only. Game URLs live only in secrets / environment variables (`GAME_FILES_URL_T2_EU`,
  `GAME_FILES_URL_T2_ES`, `GAME_FILES_URL_T2_USA`). `game/`, `asm/`, `build/`, `include/psyq/` are git-ignored.
- Never modify `.claude/settings.json`.
- Git: commit explicit paths only (no `git add -A`), no amend, no force push, `git pull --no-rebase origin master`
  before pushing to `master`. Never `pkill -f`. Every commit ends with the trailers the session gives
  (Co-Authored-By / Claude-Session). No model names anywhere in the repo.
- The user does not review PRs: verified work (the matching build still OK) goes straight to master. Open a PR only
  when asked.
- Disk in the cloud container is small: delete builds/dumps when done (`rm -rf build asm` is always safe: the build
  regenerates them); agents in worktrees must clean up. Only the USA disc image is kept (`game/usa.img`).

## Build cheatsheet

- `python3 tools/build.py [prog ...] [--no-split]`: splat + assemble + link of each `config/<prog>.yaml`, sha1 compared
  with the retail file (USA; `--version eu` for config/eu). Programs: `boot` (SCUS_944.54), `main` (MAIN.EXE), the overlays `a00`..`a0l`, `crd`, `demo`,
  `game`, `opn`, `sop` (BIN/*.BIN).
- `python3 -I tools/funcstats.py --csv build/funcs.csv`: function census (Psy-Q 4.4 library by signature, code shared
  between programs, game code left).
- `python3 -I tools/progress.py`: functions / bytes in C per program.
- C lives in `src/<prog>/*.c` (`INCLUDE_ASM` for what is not decompiled yet, `include/common.h`); see docs/STATUS.md.
- `python3 -I tools/ccheck.py src/main/<file>.c`: compile with the game's compiler (gcc 2.8.1 + ASPSX 2.79,
  docs/COMPILER.md) and compare every function in the file with the retail bytes.
- `python3 -I tools/import_names.py /opt/tomba2edit --write [--eu]`: names from Tomba2Edit (docs/TOMBA2EDIT.md).
- `python3 -I tools/vermatch.py`: how much USA code is found in the EU / ES builds.
- `python3 -I tools/gen_configs.py game/usa [--force] [--out config/eu]`: regenerates the first configs (keeps hand-made ones without --force).

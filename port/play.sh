#!/usr/bin/env bash
# One command for players (Linux or WSL2 on Windows): builds what is missing, then starts the port in a window.
#   bash port/play.sh [port options...]       e.g. bash port/play.sh --viewer-arg --fullscreen
# Needs the extracted USA disc in game/usa/ and its image game/usa.img (tools/disc_unpack.sh), the matching build's
# toolchain (tools/session_bootstrap.sh --no-build), cmake, ninja, gcc-multilib and libsdl2-dev.  docs/PORT.md §0.
set -euo pipefail
cd "$(dirname "$0")/.."
[ -s game/usa/MAIN.EXE ] || { echo "game/usa/MAIN.EXE is missing: bash tools/disc_unpack.sh YOUR_DISC.bin game/usa"; exit 1; }
[ -s build/main.elf ] && [ -s build/a0l.elf ] || python3 tools/build.py
if [ ! -x build/port/tomba2 ] || [ ! -x build/port/tomba2-view ]; then
  cmake -S port -B build/port -G Ninja && cmake --build build/port
fi
[ -x build/port/tomba2-view ] || { echo "no build/port/tomba2-view: install libsdl2-dev and run this again"; exit 1; }
exec build/port/tomba2 --window "$@"

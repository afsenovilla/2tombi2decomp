#!/usr/bin/env bash
# Fetch and extract one Tombi! 2 disc from its GAME_FILES_URL_T2_<NAME> environment variable:
#   bash tools/disc_fetch.sh EU        (or ES, USA)
# -> game/<name>/ (the disc's files) and game/<name>.img (the image, kept only for USA, the reference version).
# Ignored by git (never committed). Does nothing when game/<name>/MAIN.EXE is already there.
set -eu
NAME="${1:?disc name: EU, ES or USA}"; V="GAME_FILES_URL_T2_$NAME"
HERE="$(cd "$(dirname "$0")" && pwd)"
D="$(dirname "$HERE")/game/$(printf '%s' "$NAME" | tr 'A-Z' 'a-z')"
[ -s "$D/MAIN.EXE" ] && { echo "$D is already there"; exit 0; }
[ -n "${!V:-}" ] || { echo "$V is not set: add it to the cloud environment's settings and start a new session"; exit 1; }
T="$(mktemp -d)"; trap 'rm -rf "$T"' EXIT
bash "$HERE/ci_download.sh" "${!V}" "$T/dl" 10000000
bash "$HERE/disc_unpack.sh" "$T/dl" "$D"
if [ -s "$D.img" ] && [ "$NAME" != USA ]; then rm -f "$D.img"; fi
du -sh "$D"

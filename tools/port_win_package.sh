#!/bin/bash
# Builds the Windows release zip of the port (docs/PORT.md §0.2): tomba2.exe, tomba2-view.exe, tomba2-launcher.exe,
# SDL2.dll, README.txt, LICENSE-SDL2.txt.  No game data goes into it (the exe reads the player's disc image).
#
#   bash tools/port_win_package.sh OUT.zip [SDL2_MINGW_DIR]
#
# Needs: the matching build (python3 tools/build.py: build/*.elf, build/*.bin, asm/ are read at build time only),
# gcc-mingw-w64-i686, cmake, ninja, zip.  SDL2_MINGW_DIR is the i686-w64-mingw32 folder of
# SDL2-devel-2.30.11-mingw.tar.gz; without it the tarball is downloaded into build/sdl2-mingw (sha256 checked).
# The zip and the executables are build products: never commit them.
set -euo pipefail
cd "$(dirname "$0")/.."
OUT=${1:?usage: tools/port_win_package.sh OUT.zip [SDL2_MINGW_DIR]}
SDL=${2:-}
SDL_VER=2.30.11
SDL_SHA256=0590db0a47b564aab92499ed03eaa75db9aee17c371080caa3b05df9d49d9ff9
if [ -z "$SDL" ]; then
  mkdir -p build/sdl2-mingw
  tgz=build/sdl2-mingw/SDL2-devel-$SDL_VER-mingw.tar.gz
  if [ ! -f "$tgz" ]; then
    curl -sSL -o "$tgz" "https://github.com/libsdl-org/SDL/releases/download/release-$SDL_VER/SDL2-devel-$SDL_VER-mingw.tar.gz"
  fi
  echo "$SDL_SHA256  $tgz" | sha256sum -c -
  tar xzf "$tgz" -C build/sdl2-mingw
  SDL=$PWD/build/sdl2-mingw/SDL2-$SDL_VER/i686-w64-mingw32
fi
[ -f "$SDL/bin/SDL2.dll" ] || { echo "no SDL2.dll in $SDL/bin"; exit 1; }
cmake -S port -B build/port-win -G Ninja -DCMAKE_TOOLCHAIN_FILE="$PWD/port/cmake/mingw-i686.cmake" -DPORT_SDL2_MINGW="$SDL" >/dev/null
cmake --build build/port-win
stage=$(mktemp -d)
dir=$stage/Tomba2-port-win32
mkdir -p "$dir"
cp build/port-win/tomba2.exe build/port-win/tomba2-view.exe build/port-win/tomba2-launcher.exe "$SDL/bin/SDL2.dll" "$dir/"
sed 's/$/\r/' port/README-windows.txt > "$dir/README.txt"
lic=$(dirname "$SDL")/LICENSE.txt
[ -f "$lic" ] && sed 's/$/\r/' "$lic" > "$dir/LICENSE-SDL2.txt"
i686-w64-mingw32-strip "$dir/tomba2-view.exe" "$dir/tomba2-launcher.exe"
rm -f "$OUT"
out_abs=$(cd "$(dirname "$OUT")" && pwd)/$(basename "$OUT")
(cd "$stage" && zip -q -r -9 "$out_abs" Tomba2-port-win32)
rm -rf "$stage"
unzip -l "$out_abs"
sha256sum "$out_abs"

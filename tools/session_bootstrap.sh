#!/usr/bin/env bash
# Prepares a fresh cloud session (or any Linux box) for the Tombi! 2 decomp, from a clean clone:
#   1. system packages and Python modules (splat, spimdisasm, ...)
#   2. the PS1 toolchain (tools/setup_native.sh: old-gcc 2.7.2, maspsx, Psy-Q headers -> include/psyq, ignored)
#   3. the discs: USA (reference) always, EU and ES when their variables are set (tools/disc_fetch.sh)
#   4. the Psy-Q 4.4 object signatures (lab313ru/psx_psyq_signatures, outside the repo) for tools/funcstats.py
#   5. the matching build of every program (tools/build.py) as the smoke test
# Every step is skipped when its result is already there.   tools/session_bootstrap.sh [--no-build]
set -euo pipefail
cd "$(dirname "$0")/.."
BUILD=1; [ "${1:-}" = --no-build ] && BUILD=0
log() { printf '\n== %s\n' "$*"; }
SUDO=""; [ "$(id -u)" = 0 ] || SUDO="sudo"

log "1/5 packages"
if ! command -v mipsel-linux-gnu-as >/dev/null || ! command -v 7z >/dev/null; then
  $SUDO apt-get update -qq
  $SUDO apt-get install -y -qq binutils-mipsel-linux-gnu ninja-build unzip curl p7zip-full megatools >/dev/null
fi
python3 -c "import spimdisasm, rabbitizer, yaml, splat" 2>/dev/null || {
  python3 -m pip install -q -r tools/requirements.txt
  python3 -m pip install -q --no-deps splat64==0.35.2
}
python3 -c "import pylibyaml" 2>/dev/null || python3 -c "import site,os; open(os.path.join(site.getsitepackages()[0],'pylibyaml.py'),'w').write('# optional accelerator stub\n')"

log "2/5 PS1 toolchain"
[ -x /opt/oldgcc/gcc-2.7.2-psx/cc1 ] && [ -d include/psyq ] && [ -d /opt/maspsx ] || bash tools/setup_native.sh

log "3/5 discs"
bash tools/disc_fetch.sh USA
for N in EU ES; do V="GAME_FILES_URL_T2_$N"; [ -n "${!V:-}" ] && bash tools/disc_fetch.sh "$N" || echo "$V not set: skipped"; done
echo "f41c4065788e8c838cbd8b22f0fff6d4bc7de49a  game/usa/MAIN.EXE" | sha1sum -c --quiet - || { echo "game/usa/MAIN.EXE is not the SCUS-94454 one"; exit 1; }

log "4/5 Psy-Q signatures"
[ -d /opt/psyq_sigs/440 ] || git clone -q --depth 1 https://github.com/lab313ru/psx_psyq_signatures /opt/psyq_sigs
# Tomba2Edit (no license: read only, never copied here): USA names and USA->EU maps for tools/import_names.py
[ -f /opt/m2c/m2c.py ] || { git clone -q --depth 1 https://github.com/matt-kempster/m2c /opt/m2c && python3 -m pip install -q pycparser graphviz; }
[ -f /opt/permuter/permuter.py ] || { git clone -q --depth 1 https://github.com/simonlindholm/decomp-permuter /opt/permuter && python3 -m pip install -q toml Levenshtein; }
command -v mips-linux-gnu-objdump >/dev/null || ln -sf "$(command -v mipsel-linux-gnu-objdump)" /usr/local/bin/mips-linux-gnu-objdump   # the permuter looks for this name
[ -d /opt/tomba2edit/decomp ] || git clone -q --depth 1 https://github.com/SiergiejW/Tomba2Edit /opt/tomba2edit

[ "$BUILD" = 1 ] || { log "done (--no-build)"; exit 0; }
log "5/5 matching build"
python3 tools/build.py
[ -s game/eu/MAIN.EXE ] && python3 tools/build.py --version eu

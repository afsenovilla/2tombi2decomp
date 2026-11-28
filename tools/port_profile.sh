#!/bin/bash
# tools/port_profile.sh OUTDIR CARD.mcd [JOBS]: the --interp-profile runs of docs/PORT.md 0.6 (attract 6000 frames,
# New Game 9600, Load Game from CARD 6000, --debug-warp into every area A00..A0L at spawns 0, 1, 2: 3400 frames each),
# one OUTDIR/<run>.csv each; then: python3 -I tools/port_hot.py OUTDIR/*.csv
# Needs build/port/tomba2 (docs/PORT.md 1). Work dirs are deleted after each run; only the csv files are kept.
set -u
O=$(realpath -m "$1"); CARD=$(realpath "$2"); J=${3:-4}
cd "$(dirname "$0")/.."
mkdir -p "$O"
B=build/port/tomba2
LG="300:right:4,400:cross:4,700:cross:4,900:cross:4,1000:left:4,1050:cross:4,2400:right:200,2650:cross:10x3/40,2800:left:150,3000:right+cross:20x4/60"
run() { n=$1; shift; d=$O/work-$n; rm -rf "$d"; mkdir -p "$d"; cp "$CARD" "$d/tomba2_mc0.mcd"
  timeout 1500 $B --save-dir "$d" --interp-profile "$O/$n.csv" "$@" > "$d/log.txt" 2>&1; echo "$n rc=$?"; rm -rf "$d"; }
run attract --frames 6000
run newgame --frames 9600 --pad-script 400:start,600:cross,800:cross,1000:cross,1200:cross,1400:start,6000:circle:10x15/60
run loadgame --frames 6000 --pad-script $LG,4000:right:300,4400:cross:10x5/50,4800:left:300
k=0
for a in 0 1 2 3 4 5 6 7 8 9 A B C D E F 10 11 12 13 14 15; do for sp in 0 1 2; do
  run area$a-$sp --frames 3400 --pad-script $LG --debug-warp 1500:$a:$sp &
  k=$((k + 1)); [ $((k % J)) = 0 ] && wait
done; done; wait

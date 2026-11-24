# Tomba2Edit (external reference)

[SiergiejW/Tomba2Edit](https://github.com/SiergiejW/Tomba2Edit): a modding / translation / asset tool for Tomba! 2
(PyQt6), built on Tomba Club research ([wiki](https://tomba.club/wiki/Tomba!_2:_The_Evil_Swine_Return/Technical_information)).
Reviewed 2026-11-13 (commit 1f0b0c6) and again 2026-11-24 (release 0.5.0, commit b3fd4a6; section below). The repo has **no license file**: we read it, use the facts it states (names,
addresses, format descriptions) with credit, and copy none of its code or data files. Clone it outside this repo:
`git clone --depth 1 https://github.com/SiergiejW/Tomba2Edit /opt/tomba2edit` (the bootstrap does).

## What it has that we use

| Item | Where in Tomba2Edit | Use here |
|---|---|---|
| ~4950 USA-retail symbols (1022 real names, the rest Ghidra `FUN_*`), from an annotated Ghidra decomp of the USA `MAIN.EXE` + overlays (the `.c` itself is not in the repo) | `decomp/symbols_us.json` `{name: [image, us_addr]}` | `tools/import_names.py` |
| USA -> other build address maps (EU, ES, FR, DE, IT, JP, JP demo, US demo, two prototypes 0928 / 1111) | `decomp/builds/<build>.json`: `exe_base`, `overlay_base`, `area_base`, per image `code` runs `[us_addr, build_addr, words]`, MAIN `data` ranges, `unsettled` | translating names to EU; confirms our load addresses: EU overlays 0x80109D84, OPN/CRD area 0x80188000 (USA overlays 0x80108F9C) |
| Area names per overlay (A00 Town of the Fishermen, A01 Large Mine Underground, A02 Coal Mining Town, A03 Trolley minigame, A04 Kujara Ranch, A05 Kujara Ranch Summit, A06 Donglin Forest, A07 Circus Village, A08 Water Temple, A09 question-mark room, A0A..A0F the boss pigs, ...) | `labels/us-retail.json` | naming / plan |
| `TOMBA2.IDX/DAT/IMG` layout (below), DAT resource formats, IMG compression | `formats/archive/idx_parser.py`, `format_detect.py`, `formats/images/img_codec.py` | docs/DISCS.md, the port later |
| A MIPS interpreter that runs area code to place objects | `psx/`, `game/actor_sim.py` | ideas for `tools/psxemu` |
| Other builds known to exist: FR, DE, IT retail; JP retail and demo; USA demo; prototypes "0928" and "1111" | `decomp/builds/` | future versions |

## Name import (tools/import_names.py)

USA (the reference) takes Tomba2Edit's addresses as they are; `--eu` translates them with the EU run table. A name is
kept only when it lands exactly on a function start of our splat split. **Tomba2Edit parks names it could not place on
one shared address** (40 A00 names on 0x801467BC, 13 A04 names on 0x8013F6E4, ...): 133 names sit on addresses shared
by several names and are all dropped. Result: **USA 886 functions named, EU 885** (MAIN 451, A00 ~210, the rest a few
per overlay); 3 land mid-function in USA.

Function starts: of Tomba2Edit's 3935 unnamed `FUN_*` addresses, 3817 are function starts of our USA split; 118 are
not (MAIN 18, A05 18, A08 18, A04 11, ...): either Ghidra splits where splat does not, or Ghidra is wrong. Splat finds
more functions overall (7037 against ~4800 known to Tomba2Edit). Checking those 118 is open. Lines carry `// t2e` in `config/symbol_addrs_*.txt`; hand-made names never
do and are never overwritten. The 29 programs still rebuild byte-identical with the names.
Names in Tomba2Edit's style (`f_UpdateCircusSeesawLaunchedActor`) are kept as given; Psy-Q functions have their SDK names.

## Containers (from its parser)

- `TOMBA2.IDX`: 48 chunks of 0x800 bytes, one per "area" (load unit). Chunk header: u32 `img_start, img_end,
  dat_start, dat_end, count`, then `count` u32 pointers into the chunk's DAT range ("SDAT" entries); the last 0x700
  bytes of the chunk are a "trail" table of (start, end) DAT pairs (shared files every area also lists). A slot whose
  start equals the next one's is empty (9 on retail).
- `TOMBA2.DAT`: the files, untagged (no magic numbers anywhere); types found by shape: SMST (models), MDAT (level
  geometry + DRWA grid), SCLD (collision), DRWB (52x52 flag maps), BGMP (backgrounds), SPRT (sprites), TXTD / TXT1 /
  TXT2 (text), ANMP family (TANP, MDAP, ALFP, BETP, ALFD: animation tables).
- `TOMBA2.IMG`: per area, the VRAM as rectangular shards, each LZ77-compressed with only seven back distances (1, or
  the row above give or take 3 columns): byte = `amount<<3 | how`.

## Release 0.5.0 (reviewed 2026-11-24, commit b3fd4a6)

New since 1f0b0c6: level / event / NPC editors, character swap, warp destinations, an item scan of the NPC handlers
(`docs/npc-item-scan.md`), `game/native_decode.py` (a reader of handler code that says what it does in words) and
`game/decomp_view.py`, which shows Ghidra's C of a handler from `decomp/MAIN.EXE_US_DECOMP.c`. **That C export is
still not in the repo** (not shipped, so nothing to compare against), and `decomp/symbols_us.json` is unchanged: no
new function names (every engine routine the new code calls already has its `t2e` name here). Nothing in it changes
bytes, so it gives no matches; what it adds is meaning:

- Globals (USA addresses; not renamed here yet, the C uses `D_` names): `0x800BF80A` item-use flag, `0x800BF80B` the
  item Tomba is using, `0x800BF80E` Tomba's cutscene control, `0x800BF817` the current interior (`src_Interior`),
  `0x800BF83A` warp destination (u16: area << 8 | arrival index), `0x800BF844` the spawned pickup, `0x800BF854` the
  linked door, `0x800BFAB4` the inventory table (a byte per item id), `0x800A54A8` warp spawn coordinates (a pointer
  per area), `0x800A55B0` section base index per area, `0x800A2B84` section name pointers, `0x800ECF58` the file
  table (a pointer per file id), `0x800A3FA8`.. the costume body tables (Tomba, Squirrel 0x800A4030, Wing 0x800A40C8,
  Pig 0x800A4160, Pig Robes 0x800A41E8, Invisible 0x800A4270).
- The NPC skeleton (AGENTS.md "Round 10 / 11 forms") in words, from Tomba2Edit's generated talker handler (a copy of
  A00's 0x80121978): `a[4]` phase 0 init / 1 run / 3 release (`func_8007A624`); init builds the multi-part model
  (`f_InitializeMultiPartActorModel` with the file table entry), starts animation 0, sets the talk box (+0x80..0x86),
  scale (+0xB8..0xBC), yaw (+0x56), `a[0] = 9`; run starts the script (`f_InitializeActorScript`), `a[5] = 1` while it
  runs, `a[0x70] == 255` when it is done, then animation, render queue, transforms and `a[0x2B] = 0`. These are
  comments in include/actor.h (`T2E`).
- Item routines: give 0x8004D4C4 / 0x8004D4F4 / 0x8004D338, take 0x8004D604 / 0x8004D650 / 0x8004D688, pickups
  0x8006FB0C / 0x8006FF10 (already named).

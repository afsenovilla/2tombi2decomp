# The Tombi! 2 discs

Survey of the three retail discs (2026-11-13). Measured with `tools/disc_unpack.sh` / `tools/isoext.py` (file tree),
`tools/gen_configs.py` + `tools/build.py` (code boundaries, proven by byte-identical rebuilds), `tools/funcstats.py`
(library) and `tools/vermatch.py` (version comparison). No game data is in the repo.

| | EU | Spain | USA (reference) |
|---|---|---|---|
| Title | Tombi! 2 | Tombi! 2 - Contra los cerdiablos | Tomba! 2 - The Evil Swine Return |
| Serial / boot file | SCES-02147, `SCES_021.47` | SCES-02687, `SCES_026.87` | **SCUS-94454**, `SCUS_944.54` |
| Volume creation date | 1999-12-28 09:00 | 1999-12-28 09:00 | 1999-12-24 12:30 |
| Variable | `GAME_FILES_URL_T2_EU` | `GAME_FILES_URL_T2_ES` | `GAME_FILES_URL_T2_USA` |
| `MAIN.EXE` sha1 | `6bcee82bde552b9c044330bcc8e1889e2b80b107` | `410bd51f07893370bcf4aa7fdc2412afa38ca96a` | `f41c4065788e8c838cbd8b22f0fff6d4bc7de49a` |
| boot exe sha1 | `8832858904bbccb88ff777e359448eee0f09f485` | `39e0b3175fe3963a397b28e355bd50ac61098e08` | `9f68ffd6e4dfa9f9ff6ba6818760ee4c625be421` |
| Text language | English | Spanish | English |

Note: the USA serial is SCUS-94454 (the task notes said 94464). The volume dates are mastering dates, not build dates;
no build date string was found in the executables (no `__DATE__`).

## File layout

Same 43 files on every disc, at the root (the USA demo had them under `TOMBA2/`):

| Path | What | EU size |
|---|---|---:|
| `SCES_021.47` | boot exe (`SYSTEM.CNF` BOOT), PS-X EXE, text 0x80010000, 0x28000 B, entry 0x80017B90; Psy-Q library (52 KB) + 15 small game functions + ~100 KB data; loads `MAIN.EXE` | 165888 |
| `MAIN.EXE` | the game, PS-X EXE, text 0x80010000, 0xAF000 B, entry 0x80089DAC | 718848 |
| `BIN/A00..A08.BIN`, `A0A..A0L.BIN` | area overlays (20), loaded at 0x80109D84 | 14 KB .. 285 KB |
| `BIN/A09.BIN` | area overlay, odd size (22125 B) | 22125 |
| `BIN/GAME.BIN`, `DEMO.BIN` | overlays at 0x80106D80 | 11912, 12284 |
| `BIN/OPN.BIN`, `CRD.BIN` | overlays at 0x80188000 (opening, credits) | 13596, 25092 |
| `BIN/SOP.BIN` | overlay at 0x80109D84 (story intro) | 17672 |
| `BIN/START.BIN` | data: CD file names (`\CD\SWDATA.BIN;1`, `\CD\TOMBA2.SND;1`, ...) | 1652 |
| `CD/TOMBA2.IDX` | 96 KiB index: u32 (start, end) byte-offset pairs, sparse (1025 non-empty slots, 371 distinct ranges) | 98304 |
| `CD/TOMBA2.DAT` | packed resources; starts with (u16 count, u16 sector) pairs | 9592832 |
| `CD/TOMBA2.IMG` | packed images: count + VRAM rectangles (x, y, w, h, size) | 6295552 |
| `CD/TOMBA2.SND` | sound banks: header of u16 offsets, then plain `pBAV` / `pQES` | 3698688 |
| `CD/SWDATA.BIN` | 4 KiB table (identical on all three discs) | 4096 |
| `CD/BGM.XA`, `DEMO.XA`, `VOICE.XA` | XA audio (BGM identical on all discs; VOICE differs per language) | 151 MB, 61 MB, 60 MB |
| `MOVIE/LOGO.STR`, `OP.STR`, `END.STR` | FMV (identical EU/ES; USA `END.STR` differs) | 2.7, 21, 25 MB |

The container formats are described by Tomba2Edit (docs/TOMBA2EDIT.md "Containers"): IDX = 48 chunks of 0x800
(IMG/DAT ranges + pointer list + a trail table), DAT = untagged files (models, geometry, collision, text, animation),
IMG = per-area VRAM shards with a small LZ77. (The rows above describing IDX as flat (start, end) pairs were a first
guess; the trail tables are what looked like that.)

## Executables and overlays (USA, the reference)

Every program rebuilds byte-identical from the splat disassembly (`python3 tools/build.py`: 29 / 29 OK; EU
`--version eu`: 29 / 29 OK). Text = the `asm` subsegment of `config/<prog>.yaml` (what is before it is a pointer table /
rodata, after it data).

Load addresses per version (from the overlays' `jal` targets landing on prologues; EU and USA confirmed by Tomba2Edit's
build tables): USA areas + SOP 0x80108F9C, GAME/DEMO 0x80106228, OPN/CRD 0x8018A000; EU 0x80109D84, 0x80106D88,
0x80188000.

| Program | File | Load | Size | Text | Text size |
|---|---|---|---|---|---|
| `a00` | `BIN/A00.BIN` | 0x80108F9C | 0x459A8 | 0x8010A33C..0x801469BC | 0x3C680 |
| `a01` | `BIN/A01.BIN` | 0x80108F9C | 0x316DC | 0x80109F7C..0x801346C0 | 0x2A744 |
| `a02` | `BIN/A02.BIN` | 0x80108F9C | 0x3112C | 0x8010A528..0x801283C4 | 0x1DE9C |
| `a03` | `BIN/A03.BIN` | 0x80108F9C | 0x1326C | 0x80109024..0x8011195C | 0x8938 |
| `a04` | `BIN/A04.BIN` | 0x80108F9C | 0x3D3A4 | 0x8010A514..0x8013FA74 | 0x35560 |
| `a05` | `BIN/A05.BIN` | 0x80108F9C | 0x392B4 | 0x8010A32C..0x8013B24C | 0x30F20 |
| `a06` | `BIN/A06.BIN` | 0x80108F9C | 0x456BC | 0x8010A518..0x80141D98 | 0x37880 |
| `a07` | `BIN/A07.BIN` | 0x80108F9C | 0x38158 | 0x8010A660..0x801315A0 | 0x26F40 |
| `a08` | `BIN/A08.BIN` | 0x80108F9C | 0x40F8C | 0x8010A51C..0x80141434 | 0x36F18 |
| `a09` | `BIN/A09.BIN` | 0x80108F9C | 0x566D | 0x80109078..0x8010E004 | 0x4F8C |
| `a0a` | `BIN/A0A.BIN` | 0x80108F9C | 0x1EE38 | 0x80109314..0x80118E5C | 0xFB48 |
| `a0b` | `BIN/A0B.BIN` | 0x80108F9C | 0x1C368 | 0x801092BC..0x80118274 | 0xEFB8 |
| `a0c` | `BIN/A0C.BIN` | 0x80108F9C | 0x1E1C0 | 0x801092D4..0x80118C2C | 0xF958 |
| `a0d` | `BIN/A0D.BIN` | 0x80108F9C | 0x1D328 | 0x80109304..0x801174D8 | 0xE1D4 |
| `a0e` | `BIN/A0E.BIN` | 0x80108F9C | 0x1E6F0 | 0x80109308..0x80118034 | 0xED2C |
| `a0f` | `BIN/A0F.BIN` | 0x80108F9C | 0x2114C | 0x80109320..0x8011A9CC | 0x116AC |
| `a0g` | `BIN/A0G.BIN` | 0x80108F9C | 0x463C | 0x80109180..0x8010D2AC | 0x412C |
| `a0h` | `BIN/A0H.BIN` | 0x80108F9C | 0x36C0 | 0x801090DC..0x8010C58C | 0x34B0 |
| `a0i` | `BIN/A0I.BIN` | 0x80108F9C | 0x3B30 | 0x801090F0..0x8010CA10 | 0x3920 |
| `a0j` | `BIN/A0J.BIN` | 0x80108F9C | 0x4A7C | 0x801090C4..0x8010D288 | 0x41C4 |
| `a0k` | `BIN/A0K.BIN` | 0x80108F9C | 0x16CC4 | 0x801095C8..0x801186C0 | 0xF0F8 |
| `a0l` | `BIN/A0L.BIN` | 0x80108F9C | 0x12450 | 0x80109208..0x801131BC | 0x9FB4 |
| `boot` | `SCUS_944.54` | 0x80010000 | 0x29000 | 0x80010D54..0x8001FB5C | 0xEE08 |
| `crd` | `BIN/CRD.BIN` | 0x8018A000 | 0x61E4 | 0x8018A1E8..0x8018FEC4 | 0x5CDC |
| `demo` | `BIN/DEMO.BIN` | 0x80106220 | 0x14FC | 0x801062DC..0x801076FC | 0x1420 |
| `game` | `BIN/GAME.BIN` | 0x80106220 | 0x2D74 | 0x80106374..0x80108F58 | 0x2BE4 |
| `main` | `MAIN.EXE` | 0x80010000 | 0xAF000 | 0x8001CAC0..0x8009D090 | 0x805D0 |
| `opn` | `BIN/OPN.BIN` | 0x8018A000 | 0x351C | 0x8018A13C..0x8018D378 | 0x323C |
| `sop` | `BIN/SOP.BIN` | 0x80108F9C | 0x44FC | 0x80109164..0x8010C95C | 0x37F8 |

Overlay format (both versions): word 0 is an ID (A00 = 0x0A, ..., A0L = 0x1F, START 6, DEMO 7, GAME 8, SOP 0x20, OPN 0x22, CRD 0x23),
followed by a table of pointers into the overlay (handlers, jump tables). All area overlays of a version load at the same
address (above).

A04 and A05 each contain one GTE `avsz4` encoded with different flag bits (`0x4B58002E`, standard `0x4B68002E`); `tools/build.py` emits
GTE ops as `.word` so the assembler macro cannot change the flag bits.

## Text

Plain 8-bit text in the executables: ASCII (EU, USA), ISO-8859-1 for the Spanish accents (`dif\xedcil` = "difícil").
EU is English only (no multi-language menus found in MAIN.EXE).

## Psy-Q library

`$Id` strings: `sys.c 1.140 (1998-01-12)`, `intr.c 1.75`, `bios.c 1.86`, "Library Programs (c) 1993-1997", identical
on the three discs and in both executables. Object signatures of every Psy-Q release (lab313ru/psx_psyq_signatures,
whole objects, wildcarded relocations) matched against MAIN.EXE:

| Psy-Q | 3.6 | 3.7 | 4.0 | 4.1 | 4.2 | 4.3 | **4.4** | 4.5 | 4.6 | 4.7 |
|---|---|---|---|---|---|---|---|---|---|---|
| objects / bytes | 46 / 5.6 K | 60 / 8.0 K | 64 / 8.5 K | 190 / 65 K | 200 / 68 K | 213 / 74 K | **245 / 117 K** | 236 / 104 K | 227 / 73 K | 228 / 73 K |

**T2 links the Psy-Q 4.4 libraries** (T1 linked 3.x-era ones, sys.c 1.129). Library functions per program
(`tools/funcstats.py`, functions covered by a 4.4 object signature):

- `MAIN.EXE`: 573 functions, 117 KB: LIBSND 143, LIBCD 71, LIBGPU 66, LIBPAD 60, LIBAPI 51, LIBSPU 49, LIBGTE 30,
  LIBETC 28, LIBC2 26, LIBCARD 19, LIBPRESS 18 (MDEC), LIBGS 4, LIBDS 4, LIBSN 3, LIBC 1.
- boot exe: 283 functions, 53 KB: LIBCD 72, LIBGPU 70, LIBAPI 45, LIBETC 31, LIBSPU 22, LIBPRESS 18, LIBC2 16, ...
- overlays: none.

The compiler version (gcc 2.7.2 vs 2.8.1 based CC1PSX, ASPSX version) is not determined yet: the first C files will
tell.

## USA vs EU vs ES

EU and ES are **separate builds** (relinked, different addresses everywhere), not data patches. USA functions found
in the same program of the other disc (`tools/vermatch.py`, masked: call targets, `lui`, non-`$sp` offsets ignored):

| | USA functions found | bytes | byte-identical |
|---|---|---|---|
| EU | 6766 / 7037 | 2.694 / 2.828 MB | 289 |
| ES | 6750 / 7037 | 2.684 / 2.828 MB | 289 |

(Earlier, with EU as the base: ES had 6933 / 7051 of the EU functions, i.e. EU and ES are closer to each other than to
USA.) The C written for USA should carry over to EU / ES mostly, as in T1 where JP/USA reached 100 % from the PAL C.
`DEMO.BIN` differs most (the USA one is less than half the size).

# The Tombi! 2 discs

Survey of the three retail discs (2026-11-13). Measured with `tools/disc_unpack.sh` / `tools/isoext.py` (file tree),
`tools/gen_configs.py` + `tools/build.py` (code boundaries, proven by byte-identical rebuilds), `tools/funcstats.py`
(library) and `tools/vermatch.py` (version comparison). No game data is in the repo.

| | EU (reference) | Spain | USA |
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

The containers are only partly understood (above); decoding them is a later task (needed for the port, not for the
matching code). Whether data is compressed is not yet known (DAT entries have entropy ~5.8 bits/byte: tables or
lightly packed data, not LZ output).

## Executables and overlays (EU)

Every program rebuilds byte-identical from the splat disassembly (`python3 tools/build.py`: 29 / 29 OK). Text =
the `asm` subsegment of `config/<prog>.yaml` (what is before it is a pointer table / rodata, after it data).

| Program | File | Load | Size | Text | Text size |
|---|---|---|---|---|---|
| `a00` | `BIN/A00.BIN` | 0x80109D84 | 0x45860 | 0x8010B114..0x80147754 | 0x3C640 |
| `a01` | `BIN/A01.BIN` | 0x80109D84 | 0x3152C | 0x8010AD64..0x8013541C | 0x2A6B8 |
| `a02` | `BIN/A02.BIN` | 0x80109D84 | 0x30BAC | 0x8010B2DC..0x8012903C | 0x1DD60 |
| `a03` | `BIN/A03.BIN` | 0x80109D84 | 0x13268 | 0x80109E0C..0x80112740 | 0x8934 |
| `a04` | `BIN/A04.BIN` | 0x80109D84 | 0x3D1B0 | 0x8010B2EC..0x801407F0 | 0x35504 |
| `a05` | `BIN/A05.BIN` | 0x80109D84 | 0x38D78 | 0x8010B0F4..0x8013BF38 | 0x30E44 |
| `a06` | `BIN/A06.BIN` | 0x80109D84 | 0x452A0 | 0x8010B2F8..0x80142A08 | 0x37710 |
| `a07` | `BIN/A07.BIN` | 0x80109D84 | 0x37BC0 | 0x8010B418..0x80132244 | 0x26E2C |
| `a08` | `BIN/A08.BIN` | 0x80109D84 | 0x40BF4 | 0x8010B310..0x801421E4 | 0x36ED4 |
| `a09` | `BIN/A09.BIN` | 0x80109D84 | 0x566D | 0x80109E60..0x8010EDEC | 0x4F8C |
| `a0a` | `BIN/A0A.BIN` | 0x80109D84 | 0x1EDE0 | 0x8010A0FC..0x80119C24 | 0xFB28 |
| `a0b` | `BIN/A0B.BIN` | 0x80109D84 | 0x1C30C | 0x8010A0A4..0x80119038 | 0xEF94 |
| `a0c` | `BIN/A0C.BIN` | 0x80109D84 | 0x1E168 | 0x8010A0BC..0x801199F4 | 0xF938 |
| `a0d` | `BIN/A0D.BIN` | 0x80109D84 | 0x1D2CC | 0x8010A0EC..0x8011829C | 0xE1B0 |
| `a0e` | `BIN/A0E.BIN` | 0x80109D84 | 0x1E698 | 0x8010A0F0..0x80118DFC | 0xED0C |
| `a0f` | `BIN/A0F.BIN` | 0x80109D84 | 0x210E4 | 0x8010A108..0x8011B784 | 0x1167C |
| `a0g` | `BIN/A0G.BIN` | 0x80109D84 | 0x463C | 0x80109F68..0x8010E094 | 0x412C |
| `a0h` | `BIN/A0H.BIN` | 0x80109D84 | 0x36C0 | 0x80109EC4..0x8010D374 | 0x34B0 |
| `a0i` | `BIN/A0I.BIN` | 0x80109D84 | 0x3B30 | 0x80109ED8..0x8010D7F8 | 0x3920 |
| `a0j` | `BIN/A0J.BIN` | 0x80109D84 | 0x49F4 | 0x80109EAC..0x8010E038 | 0x418C |
| `a0k` | `BIN/A0K.BIN` | 0x80109D84 | 0x16B40 | 0x8010A39C..0x8011941C | 0xF080 |
| `a0l` | `BIN/A0L.BIN` | 0x80109D84 | 0x12548 | 0x80109FF0..0x8011409C | 0xA0AC |
| `boot` | `SCES_021.47` | 0x80010000 | 0x28800 | 0x80010C64..0x8001EB70 | 0xDF0C |
| `crd` | `BIN/CRD.BIN` | 0x80188000 | 0x6204 | 0x801881E8..0x8018DEE4 | 0x5CFC |
| `demo` | `BIN/DEMO.BIN` | 0x80106D80 | 0x2FFC | 0x80106F54..0x80109D5C | 0x2E08 |
| `game` | `BIN/GAME.BIN` | 0x80106D80 | 0x2E88 | 0x80106EDC..0x80109BCC | 0x2CF0 |
| `main` | `MAIN.EXE` | 0x80010000 | 0xAF800 | 0x8001CB3C..0x8009D7CC | 0x80C90 |
| `opn` | `BIN/OPN.BIN` | 0x80188000 | 0x351C | 0x8018813C..0x8018B378 | 0x323C |
| `sop` | `BIN/SOP.BIN` | 0x80109D84 | 0x4508 | 0x80109F4C..0x8010D750 | 0x3804 |

Overlay format: word 0 is an ID (A00 = 0x0A, ..., A0L = 0x1F, START 6, DEMO 7, GAME 8, SOP 0x20, OPN 0x22, CRD 0x23),
followed by a table of pointers into the overlay (handlers, jump tables). Area overlays all load at 0x80109D84
(found from `jal` targets landing on function prologues: 521 hits for A00 at that base, the next best 228; not yet
confirmed from the loader code in MAIN.EXE).

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

## EU vs ES vs USA

ES and USA are **separate builds** (relinked, different addresses everywhere), not data patches:

| | EU functions found (masked: call targets, `lui`, non-`$sp` offsets ignored) | of those byte-identical |
|---|---|---|
| ES | 6933 / 7051 (2.816 / 2.831 MB) | 335 |
| USA | 6764 / 7051 (2.694 / 2.831 MB) | 289 |

So the C written for EU should carry over to ES almost entirely and to USA mostly (as in T1, where JP/USA reached 100 %
from the PAL C). `DEMO.BIN` and `GAME.BIN` differ most (25 / 47 and 33 / 57 found in ES; USA `DEMO.BIN` is less than
half the size).

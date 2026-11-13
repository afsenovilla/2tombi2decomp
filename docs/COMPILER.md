# Compiler

**Tombi! 2 is built with Psy-Q 4.4: CC1PSX `2.8.1 SN32 BUILD 4.0.0010` (gcc 2.8.1) and ASPSX 2.79.** Matching
pipeline: old-gcc `gcc-2.8.1-psx` cc1 `-O2 -G0 -funsigned-char` + maspsx `--aspsx-version=2.79 --expand-div` + GNU as
(`tools/ccheck.py`, defaults). T1 used gcc 2.7.2 (Psy-Q 4.0 CC1PSX) and ASPSX 2.86.

## Evidence (2026-11-13)

Probed on EU first, then rechecked on USA after the switch of reference: both functions match on both.

- Library: the Psy-Q 4.4 object signatures cover the most library code (docs/DISCS.md).
- The Psy-Q 4.4 package (mkst/esa `psyq4.4`) holds exactly that pair: `CC1PSX.EXE` = "2.8.1 SN32 BUILD 4.0.0010",
  `ASPSX.EXE` = "SDevTC ASPSX version 2.79" (4.3: gcc 2.8.0 / ASPSX 2.77; 4.5: ASPSX 2.81).
- Probe functions (`src/main/ccprobe.c`), compiled with both old-gcc builds:
  - `f_StopVoicePlayback` (USA MAIN 0x8001CF2C, EU 0x8001CFA8): **matches only with gcc 2.8.1**. gcc 2.7.2 leaves the store to a global
    as a macro that the assembler expands through `$at`; the retail code (and 2.8.1) loads `%hi` into `$v0`. The
    source needs an unused 8-byte local (frame 0x20) and a `volatile` flag byte (the store is not moved into the
    `jal` delay slot).
  - `f_SetIdentityMatrix` (USA 0x80051794, EU 0x80051A8C): matches with both (written as eight `long` stores).
  - ASPSX 2.77 / 2.79 / 2.81 give the same bytes for these; 2.79 is taken from the package.
- Not yet matched (register allocation, permuter work): `f_TestAppleCollectedBit` (EU 0x8004DB10) (signed `n / 8`,
  `n - q * 8`, a game-state struct with a byte array at +0x544 based on `D_800BFFC0`) and
  `f_CopyEncodedMessageSegment` (EU 0x8004F22C) (copies bytes until 0xFA / 0xFF, then writes 0xFF; retail reuses the 0xFF
  constant register for the final store).

## Not checked

- Running the real CC1PSX 4.4 under Wine (`tools/setup_psyq.sh` can fetch it) as a reference check of old-gcc 2.8.1.
- `-G` value: no `$gp`-relative accesses seen so far (`-G0`).
- Whether overlays or the boot exe used other flags.

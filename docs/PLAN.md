# Plan (EU SCES-02147)

Numbers from `python3 -I tools/funcstats.py` on the splat split (2026-11-13). "dup" = a function whose masked word
sequence already appeared in an earlier program (the same source compiled into several overlays): it is written once.
Exact masked duplicates only; near-duplicates (the per-area copies of shared object code with small edits) are more.

| Program | Functions | Bytes | Psy-Q | dup | **Game functions** | **Game bytes** |
|---|---:|---:|---:|---:|---:|---:|
| `main` (MAIN.EXE) | 1742 | 527504 | 573 | 60 | **1109** | **403180** |
| `boot` | 298 | 57100 | 283 | 0 | 15 | 4348 |
| `game`, `demo`, `opn`, `sop`, `crd` | 196 | 74292 | 0 | 33 | 163 | 68500 |
| `a00`..`a08` (big areas) | 3638 | 1608384 | 0 | 448 | 3190 | 1489692 |
| `a09`, `a0a`..`a0f`, `a0k`, `a0l` | 1022 | 524320 | 0 | 418 | 604 | 323804 |
| `a0g`..`a0j` (small) | 158 | 61576 | 1* | 99 | 58 | 28848 |
| **Total** | **7051** | **2831136** | **858** | **1019** | **5174** | **2314396** |

\* a 16-byte false positive. For scale: T1 PAL had 1.53 MB of game code (100 % matched); T2 has ~2.3 MB, about 1.5x.

## Order

1. **Infrastructure** (before C): objdiff units + `tools/build_report.py` adapted from T1 (report.json per program),
   the decomp.dev project and `.github/workflows/report.yml` with the disc cache; a C build path in `tools/build.py`
   (old-gcc + maspsx, `INCLUDE_ASM` for the rest) and a per-function check (`ncheck`-style) and `permute.py`.
2. **Compiler identification** on a few small MAIN.EXE leaf functions (gcc 2.7.2 vs 2.8.1 CC1PSX, maspsx options).
3. **Psy-Q 4.4 library** (573 functions in MAIN, 283 in boot): name them from the signatures
   (`config/symbol_addrs_*.txt`), then C from existing Psy-Q decompilations (as T1 did, THIRD_PARTY_NOTICES) where the
   4.4 source matches; not counted as game code.
4. **MAIN.EXE game code** (1109 functions, 403 KB): the engine (task system, objects, rendering, CD/loader, menus,
   save, sound glue). Everything else calls it, so names and structs found here serve all the overlays.
5. **Small overlays**: `game`, `demo`, `opn`, `sop`, `crd`, `boot` (178 functions, 73 KB) — quick wins, check the
   pipeline end to end, and identify the loader (confirms the overlay load addresses).
6. **Area overlays, most shared first**: `a0b`..`a0f`, `a0g`..`a0j` (half their functions are dups), then `a0a`,
   `a0k`, `a0l`, `a09`, then the big ones `a00`..`a08` (3190 functions, 1.49 MB). Near-duplicate pairing between areas
   (T1's `demo_pair.py` approach) will cut this further.
7. **ES and USA** from the EU C (separate configs per version as in T1), then the containers and the port.

## Estimate

Unknown until the first hundred functions show the pace. Reference: T1 went from all-asm to 100 % of 1.53 MB with
heavy automation (auto-decompile + permuter + sweeps across versions). With the same tooling, T2 is ~1.5x that amount
of code, and the per-area duplication should help. A first milestone to measure against: MAIN.EXE library + 25 % of
its game code.

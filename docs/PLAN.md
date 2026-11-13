# Plan (USA SCUS-94454, the reference)

Numbers from `python3 -I tools/funcstats.py` on the USA splat split (2026-11-13; EU: 7051 / 5174 / 2.31 MB, the same
within 1 %). "dup" = a function whose masked word
sequence already appeared in an earlier program (the same source compiled into several overlays): it is written once.
Exact masked duplicates only; near-duplicates (the| Program | Functions | Bytes | Psy-Q | dup | **Game functions** | **Game bytes** |
|---|---:|---:|---:|---:|---:|---:|
| `main` (MAIN.EXE) | 1739 | 525776 | 572 | 60 | **1107** | **401564** |
| `boot` | 306 | 60936 | 285 | 0 | 21 | 8152 |
| `game`, `demo`, `opn`, `sop`, `crd` | 176 | 67348 | 0 | 29 | 147 | 61588 |
| `a00`..`a08` (big areas) | 3638 | 1609968 | 0 | 440 | 3198 | 1494772 |
| `a09`, `a0a`..`a0f`, `a0k`, `a0l` | 1020 | 502332 | 1* | 389 | 630 | 315436 |
| `a0g`..`a0j` (small) | 158 | 61632 | 1* | 99 | 58 | 28848 |
| **Total** | **7037** | **2827992** | **859** | **1017** | **5161** | **2310360** |

51** | **2831136** | **858** | **1019** | **5174** | **2314396** |

\* 16-byte false positives. For scale: T1 PAL had 1.53 MB of game code (100 % matched); T2 has ~2.3 MB, about 1.5x.

## Order

1. **Infrastructure** (before C; no decomp.dev report, by the user's choice): a C build path in `tools/build.py`
   (old-gcc + maspsx, `INCLUDE_ASM` for the rest) and a per-function check (`ncheck`-style) and `permute.py`.
2. **Compiler identification** on a few small MAIN.EXE leaf functions (gcc 2.7.2 vs 2.8.1 CC1PSX, maspsx options).
3. **Psy-Q 4.4 library** (572 functions in MAIN, 285 in boot): name them from the signatures
   (`config/symbol_addrs_*.txt`), then C from existing Psy-Q decompilations (as T1 did, THIRD_PARTY_NOTICES) where the
   4.4 source matches; not counted as game code.
4. **MAIN.EXE game code** (1107 functions, 402 KB): the engine (task system, objects, rendering, CD/loader, menus,
   save, sound glue). Everything else calls it, so names and structs found here serve all the overlays.
5. **Small overlays**: `game`, `demo`, `opn`, `sop`, `crd`, `boot` (168 functions, 70 KB) — quick wins, check the
   pipeline end to end, and identify the loader (confirms the overlay load addresses).
6. **Area overlays, most shared first**: `a0b`..`a0f`, `a0g`..`a0j` (half their functions are dups), then `a0a`,
   `a0k`, `a0l`, `a09`, then the big ones `a00`..`a08` (3198 functions, 1.49 MB). Near-duplicate pairing between areas
   (T1's `demo_pair.py` approach) will cut this further.
7. **EU and ES** from the USA C (separate configs per version as in T1), then the containers and the port.

## Estimate

Unknown until the first hundred functions show the pace. Reference: T1 went from all-asm to 100 % of 1.53 MB with
heavy automation (auto-decompile + permuter + sweeps across versions). With the same tooling, T2 is ~1.5x that amount
of code, and the per-area duplication should help. A first milestone to measure against: MAIN.EXE library + 25 % of
its game code.

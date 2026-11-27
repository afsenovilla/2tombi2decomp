# AGENTS.md: how to work on 2tombi2decomp

The guide for any agent (a coordinator session, a hand-matching subagent, a tools agent, or another tool that reads
AGENTS.md). Read it together with CLAUDE.md (session rules, build cheatsheet) and the newest sections of
docs/STATUS.md (current numbers, near misses, open tool work). **Keep this file, CLAUDE.md and docs/STATUS.md up to
date every time something new is learned or decided**: a recipe, a tool, a compiler fact, a decision, a pitfall.
STATUS.md is the dated log; this file is the distilled, current knowledge.

## The project in five lines

- Matching decompilation of Tombi! 2 / Tomba! 2 (PS1, 1999), reference **USA SCUS-94454**; 29 programs (boot
  SCUS_944.54, MAIN.EXE, the area overlays A00..A0L, GAME, DEMO, OPN, SOP, CRD), each rebuilt byte-identical
  (`python3 tools/build.py`, sha1 against the disc).
- **Byte-matching only** (the user's decision): no NON_MATCHING / equivalent C in src/. A function counts when its C
  compiles to exactly the retail bytes; everything else stays INCLUDE_ASM.
- Game C: `src/<prog>/<prog>.c` (one file per program). Library C (Psy-Q 4.4 and the boot region module): one file
  per function in `src/<prog>/psyq/<lib>/`. Overlay-local names of globals: `config/aliases_<prog>.ld`.
- Never commit game data, binaries, asm/, build/, include/psyq/, dumps or screenshots. English in everything
  generated; the chat with the user is in Spanish.
- Progress: `python3 -I tools/progress.py --phases`; README block: `python3 -I tools/readme_progress.py`.

## Compilers (tools/cc.py; set-up lines at the top of a C file)

- **Game code**: gcc 2.8.1 (old-gcc gcc-2.8.1-psx) `-O2 -G0 -funsigned-char` + maspsx (ASPSX 2.79) + GNU as. The
  default; no header needed.
- **Psy-Q library** (Sony built it with other compilers): try, in this order,
  1. `// CC gcc-2.8.1-psx`, `// FLAGS -O2 -G0 -mno-split-addresses`, `// AS gnu` (libgpu, libcd, libspu, libc2);
  2. the same plus `-fno-delayed-branch`;
  3. `// CC gcc-2.7.2-psx`, `// AS gnu` (libsnd, libpad, libcd/libetc statics; `-O1` once);
  4. any of these with `// CC gcc-2.8.1-nocse` instead of 2.8.1: **Sony's library compiler had no post-reload CSE**
     (no `move a2,a1` for two zero arguments, no `sllv` with a register holding 16, no `and x,v0` with v0 = 1).
     tools/setup_native.sh makes it from the stock cc1 (one byte patched, sha1 checked);
  5. **the library compiler also hoists more loop invariants around loops that contain calls** (constants and
     global loads kept in saved registers: `li s8,-1` in CdControl, the five constants of _SsVmInit). Patching the
     `loop_has_call` multiplier of scan_loop reproduces it (gcc-2.7.2-psx cc1 file offsets 0xC6C66 / 0xC6C6D,
     gcc-2.8.1 0xDC87D / 0xDC884); it is per file (CD_cachefile breaks with it). Set-ups (tools/setup_native.sh,
     sha1 checked): `// CC gcc-2.7.2-loop4` (both multipliers 4; _spu_gcSPU matches as is), `// CC gcc-2.8.1-loop2`
     (call case 2) and `// CC gcc-2.8.1-nocse-loop2`; libsweep / libnear `--loop` / `--only-loop`, pzsweep `--loop`
     and `--cc A,B` (a compiler no set-up names takes its stock family's set-ups). Under loop4 a function can get
     an unused 8-byte frame slot (_SsClose: `vars= 8`, frame 32 for retail's 24, all code equal). Without the
     patched compilers, reach the same code by hand: a constant local assigned at the end of the do/while body is
     hoisted last (`m1 = -1; } while (--count != m1);`), a long-lived local declared before the loop (`int one =
     1;`) gets reload's `li t0,K`, and `one = 1` at the top of the body keeps `x & (one << bit)` as sllv/and.
  gcc 2.7.2 gives a for / while loop with a non-constant bound an unused 8-byte frame slot: write `i = 0; if (n >
  0) do { ...; i++; } while (i < n);` (the guard compares the bound with 0; `continue` -> a goto before the
  increment); a 2.7.2 near miss with a frame 8 / 16 bytes too big is this. `la reg, sym+off` followed by stores from
  that register means gcc 2.8.1 `-mno-split-addresses` (2.7.2 folds a constant pointer into `sw sym+off`).
  The region module in boot is partly gcc 2.7.2: try it first there; CdControlF needs `AS gnu` under 2.7.2.
  Plus the asm rewrites Sony's compiler needs: `// EPILOGUE sony` (nothing in the `j $31` delay slot; ra restore then
  `addiu sp; jr ra; nop`) and `// RETURN sony` (one shared final `jr ra; nop`; `sony first` keeps an early
  `return K;` after its test; `sony thread` sends a branch to a `j ret; li v0,K` block to the return). An empty
  `__asm__ volatile("");` before the closing brace (or `goto end; ... end: __asm__ volatile(""); return r;`)
  reproduces Sony's single exit where RETURN sony is not enough (merged arm tails, early return branching to the exit
  with `move v0,zero` in the delay slot, restores after the last stores).
- Library C sources to adapt (MIT): psx_tomba (/tmp/psx_tomba), psyz (/opt/psyz/decomp/src, Psy-Q 4.0, with the
  4.0 SDK headers in /opt/psyz_inc/og made by setup_native.sh), psy-q-decomp (/opt/psy-q-decomp/src,
  `-DVERSION=40`); `tools/pzsweep.py --install` compiles their files whole and finds any pending function of the
  same bytes, named or not (`-DPERMUTER` keeps their INCLUDE_ASM out). Mark each file `// Source: ...`; keep THIRD_PARTY_NOTICES.md
  current. 4.0 differs from 4.4 in places (libsnd `_svm_voice` is 0x38 bytes in 4.4; SeqStruct `l_count`, `unk21..23`,
  `vab_id` are signed char; `_SsSndStop` has no SsUtReverbOff; the full list is in STATUS 2026-11-22 (8)).
- Jump tables: a C `switch` keeps the retail table (tools/jtbl.py rewrites %hi/%lo and bare `$Lnn` operands).
- GTE: `#include "gte.h"` (real cop2 command words over psyq/inline_c.h's placeholders).
- Functions hand-written in assembly in the original (BIOS stubs, setjmp, libgte RotMatrix*, DecDCTvlc, ...) are
  marked "asm by design" (tools/asm_by_design.py) and count as done. Game code too (`--game`, 2026-11-24): no
  stack frame plus a trapping `add` / `addi` / `sub` or an `or rd, $zero, rs` move (gcc 2.8.1 never emits either;
  none of the matched game code has one): a `// ASM by design: ...` line right above the INCLUDE_ASM line. 12
  marked, the GTE primitive-list builders of a00 / a04 / a05 / a07 / a08 / a0l. splat's `/* Handwritten function */`
  header alone means nothing (GTE macros set it).

## Order of work for a scope

0. **The work queue**: `python3 -I tools/workqueue.py <progs> [--top 30] [--max-size 0x400]` (build/queue_<progs>.csv;
   run `tools/inlined.py <progs>` first for its `inl` column): every pending function with its callees (jal targets
   resolved in its program, then MAIN / boot), how many are still pending, size, jump tables (`jt`), inlined matched
   bodies, family / exact copies; the ones that call no pending function first, then by size x exact copies. Take
   targets from the top; its last line names the pending callees that block the most functions (MAIN's
   f_PlaySoundEffect blocks 521 pending functions over all programs, 2026-11-23).
1. **Families**: `python3 -I tools/families.py --by-scope`: pending functions with exact copies in several programs.
   Match one, then `python3 -I tools/nearcopy.py <progs> --install` fills the copies. Siblings that differ in
   constants, store lists, load signedness or the place of a store around a call (the family template method):
   `python3 -I tools/sibling.py --from PROG:NAME [--src scratch.c] --install` right after the first member
   matches (all programs; the scratch need not be installed yet), or `tools/sibling.py [progs] --install` over all
   matched C (ratio 0.65, about 6 minutes for every program); its near/ files say which edits it made.
2. **Inlined bodies**: `python3 -I tools/inlined.py <progs>` (build/inlined_<progs>.csv): pending functions that
   contain a matched function inlined. Copy the matched C as a `static inline` helper (`/* NAME, inlined */`) and
   call it. Big dispatchers are usually a switch over several such handlers: `python3 -I tools/dispatch.py --list
   <progs>`, then `tools/dispatch.py PROG NAME` writes the scratch (helpers + m2c caller skeleton with the helper
   calls in place; read its notes on shared tails), fix types and the cases, ccheck, install. The same block several
   times in one pending function (an unrolled loop, a helper inlined at each use): `tools/inlined.py <progs>
   --repeats` gives each block's copies and address ranges; write it once as a `static inline` helper.
3. **Actor state machines** (the bulk of the medium / large functions left): `switch (a[4])` with sub-switches
   on a[3] / a[5], whose cases call matched handlers. Write them whole from the plain decomp.py draft: each matched
   body as `static inline`, every case in full, the case table read from the rodata jump tables (dispatch.py drafts
   are poor for these). About 3 minutes each; `python3 -I tools/statemachine.py --list [PROGS]` lists the pending
   functions with jump tables (all calls to matched functions first) and `tools/statemachine.py PROG NAME` writes
   the scratch: a header with each jump table (switch operand a[4] / a[5] / ..., every case's target, its calls
   and the matched bodies inlined there), the helpers, and the closer of the dispatch.py and decomp.py drafts. In a09-a0f, the **list walkers** follow one template:
   `l = LIST; D_1F800182 = COUNT; while (D_1F800182 != 0) { e = *l; D_1F800182--; l++; if (e[0] & 1) switch (e[2])
   {...} }` over the lists 0x1F80013C / 148 / 14C / 154, and the outer `if (*(s16 *)&COUNT == 0) return; for (p =
   D_800F2738; p; p = *(u8 **)(p + 0x24)) { if (!(p[0] & 1) || p[0x2B]) continue; ... }`.
4. **Near misses** listed in STATUS (1-12 words off), with the tools below.
   Sources checked and exhausted: Tombi! 1's C (`tools/t1sweep.py`, 2026-11-23): compiled with this pipeline it
   comes within 4 words of no pending function (the code the two games share is matched already); read T1's C only
   for idioms (T1's AnimAdvance gave f_AdvanceActorTimedFrameSequence with T2's offsets). Credit T1-derived C in
   the file (`adapted from Tombi-Decomp's NAME (src/NAME.c, MIT)`).
5. **Medium and large functions** (0x200+ bytes): the small ones are mostly done; bytes are what is left.
6. After each batch: nearcopy over your programs (copies of your new C); list copies in other scopes for the
   coordinator.

## The loop for one function

- Draft: `python3 -I tools/decomp.py NAME` (m2c, jump tables included); `--actor` types arg0 as `Actor *`
  (include/actor.h, `--actor-args 0,1` for others; also statemachine.py / dispatch.py `--actor`): far fewer casts
  (24 -> 5 on a typical state machine), the same ccheck score on 8 of 10 tries; keep the plain draft too when retail
  keeps a derived base pointer (`s1 = a + 0x60`: the plain draft has it, the struct draft folds it). Scratches get
  `#include "actor.h"`, which install_c carries into the target file; already-matched C keeps its byte-pointer forms. m2c invents constant arguments for calls
  whose register is not set on that path (decomp.py flags them after the draft: `/* decomp.py: F at ADDR: a2 not
  written on every path ... */`), and leaves "uninitialised" locals that are really incoming parameters.
- Check: `python3 -I tools/ccheck.py FILE.c --prog P --func NAME [-v] [--sbs] [--no-protos]`. `--sbs` is the
  side-by-side diff (read it, do not guess from word counts). ccheck masks relocations: only the linked build proves
  two globals are not swapped. `--no-protos` compiles as install_c will (it drops scratch prototypes).
- Search: `tools/variants.py` (several `//--` variants, `--set`, `--alts K=FILE`), `tools/permlines.py` (lines marked
  `//P`; `--exhaustive` for up to 7 lines; check that a result does not use a variable before it is set),
  `tools/regswap.py` (register-choice rewrites: declaration order, `do { } while (0)` wraps, parameter copies,
  loads before stores, cast <-> `MEMBER_AT` member, volatile reads and stores (`vstore`), duplicated tails,
  ternaries, per-path locals, empty cases (`emptycase`), `x++` for `x = K + 1` in `case K` (`caseinc`), one store
  per arm (`perarm`); early constants only with `--hacks`), `tools/sbs.py --real` / `ccheck --sbs --real`
  (relocation-only differences hidden), `tools/prio.py --prog P` (pseudo priorities and registers from the cc1 dumps next to retail's register;
  `--sched` the scheduler priorities when ccheck says `order only`), `tools/hillclimb.py`, `tools/permute.py`
  (decomp-permuter),
  `tools/magicdiv.py` (divisor of a magic-number division). Hand work from a draft beats hillclimb (about 5 minutes
  per function against hours of search); give up on a function after about 10 minutes without progress.
- Install: `python3 -I tools/install_c.py FILE.c --prog P` (game C) or `tools/install_lib.py FILE.c --prog P`
  (library files). Both check the linked build, lock per program, merge alias lines, take K&R definitions and static
  helpers, and end with `NOT INSTALLED: ...` on failure: read the last line. Write scratch C without prototypes and
  cast arguments that need s16 conversions.

## Parallel rounds (coordinator and agents)

- One coordinator, five hand-matching agents on disjoint scopes (since round 8: main game code; a00-a01; a02-a03;
  a04-a08; a09-a0l + game/demo/opn/sop/crd + boot game code; the library only in tools passes or an occasional
  round), then one tools agent alone (it implements the tool ideas of the
  round; nobody else edits tools/ meanwhile).
- Agents: touch only the scope's files; never edit tools/, never run dupsweep, never `tools/build.py` without
  `--no-split`, never `rm -rf build asm`; `-j 1` (4 CPUs for 5 agents); commit every few functions with a pathspec
  (`git add F && git commit -m MSG -- F`, include the config/aliases_<prog>.ld the C needs, in the same commit);
  never push; scratch only in the session scratchpad. Final report in English: functions per program, copies in
  other scopes, near misses (words off, scratch path), recipes, tool ideas.
- Coordinator at the end of a round: `python3 -I tools/integrate.py --since <the previous integration commit>` does
  the mechanical part in one command (never commits or pushes): clean full build (`rm -rf build asm`, build, build
  again: which src/ files sync_src rewrote and whether only whitespace changed, then commit that normalisation),
  `tools/nearcopy.py --install` and `tools/dupsweep.py --install` over all programs, full build again,
  readme_progress, progress --phases, and every commit of REF..HEAD built in a temporary worktree
  (build/tmp_integrate_wt; the programs each commit touched) with the commits that do not link (`first` = the commit
  that broke a program). About 1 minute per full build; `--only-since REF` for the link check alone. Then:
  commit what it changed, STATUS section + this file + CLAUDE.md, pull, push to master and the session branch.

## Recipe catalogue (gcc 2.8.1 -O2; the dated details are in STATUS)

**Aliasing and load / store order** (gcc 2.8 MEM_IN_STRUCT_P; `MEMBER_AT(T, p, o)` of include/common.h is the
struct-member form of a cast access, regswap `member` toggles every one)
- A scalar global is assumed not to alias a struct-field or array access at a varying address. Retail reloads a
  global after a store: access it as an array element / struct field. Retail hoists a global load above a pointer
  store: make that store a struct field, e.g. `#define S16F(p, o) (((struct { u8 pad[o]; s16 v; } *)(p))->v)`.
- A store through a plain pointer cast (`*(u32 *)((u8 *)p + 4) = v;`) is not moved across a scalar global load.
- Loads first: read globals / scratchpad values / fields into locals at the top, in retail's load order, when retail
  loads them before a run of stores (`s32 v = D_1F80009C;`, `u16 x = b[0x2E]; D = 0; a[0x2E] = x + t;`).
- A store after the copy of a field stays below its load (anti-dependence); write the statement whose value retail
  loads first earlier in source; volatile scratchpad accesses keep source order.
- Retail re-reads a stored field: write the field expression again; `*(T * volatile *)(a + off)` or
  `*(volatile u8 *)(a + off)` for a reload; a union of arrays lets CSE keep a field across stores to other fields.
- lhu + sll/sra instead of lh: the u16 was read before an aliasing store and sign-extended after it.
- A struct-member access (any mode but QImode) never aliases a fixed scalar global; to keep a global's store in
  place after struct-member stores, access the global as a struct member too (`D_800BF870.pad1[0x143]`).

**Constants and CSE**
- `n = 3; a[9] = n;` stops reuse of an older register holding 3; `s32 k = 3;` across a call keeps it in a saved
  register; `one = 1; if (x == one)`; `u8 one = 1` keeps `return 1` its own `li`; constants in saved registers around
  a loop: locals assigned at the top of the loop body; s16 locals for truncated constants (`li -1024`).
- In `case K:` a store of K + 1 is `a[4]++` (reuses the next compare constant); `s32 c = a[5]; if (c == 0) ...
  a[5] = c + 1;` folds to `li 1`; `switch (x) { case 0: x++; }` folds, `if (x == 0)` does not.

**Registers**
- Priority = floor_log2(refs) * refs / live_length (tools/prio.py); `do { } while (0)` around a statement raises
  its refs' weight and stops sched moving increments into load-delay slots.
- Declaration order of temporaries decides mult result registers; a separate C variable per path where retail
  shares a register; reuse the C variable for a derived value when retail reuses the input register
  (`sx = -sx + 0x98;`); reusing a variable (`p = f(p, k);`) moves it to a lower s-register; copy a parameter into a
  local (`u8 *a = a0;`) for s-register swaps.
- An unexplained copy register is a narrower second variable (`s32 k = load; u8 j = k;`); a u8 parameter in its own
  register: declare s32 and `x &= 0xFF`; a u8 flag passed on: s32, test `!(f & 0xFF)`, pass `(u8)f`; `s32 s = a[4]`
  for a switch variable (u8 adds an andi); `abs()` (builtin) on s32 / s16 gives `bgez/negu`.
- Compare order sets registers (`x > sum` vs `sum < x`); `(r & 0xFF) == 0`, `(a ^ b) == 0`.
- Copy the parameter into a local (`void f(u8 *a0) { u8 *a = a0; ...}`) when an argument and a derived pointer
  have swapped saved registers; dead copies in regswap / permuter output hide this.

**Control flow and layout**
- Case order in source is block order; an empty `case 2: break;` gives the `beq 1; slti 2; beqz; bnez` tree; GNU
  case ranges reproduce range tests; `case 0: default:` for a table whose entry 0 is the default; list every in-range
  case to get the table; `default: return 0;` first (or no default) for `beqz; beq 1 (v0=0 in delay); j epilogue`;
  explicit if/goto where gcc will not build retail's tree.
- Cross-jumping merges identical tails: write each case / arm in full and let gcc merge; a global stored in every
  case gives per-case `lui; li` with one shared `sh`; write a store in both branches where retail keeps two blocks.
- Bool returns: `return 1` as the shared exit with early `return 0`s gives `li v0,1` in a delay slot; separate early
  returns and `||` give different return blocks; `if (i >= n) return X;` first; `if (p) { ...; return p; } return
  NULL;` keeps v0.
- Inlined helpers with early returns: `r = 0; goto done;` per exit; `goto fail;` into a later `if (e == NULL) {
  fail: return 0; }`.
- Loops: a goto loop (`loop: ...; if (++i < n) goto loop;`) has no hoisting or strength reduction; `while (c) {}` vs
  `do {} while (c)` decides the re-materialised `lui`; `D[i].lo` inside the loop; `e[i * 4 + k]` for one pointer;
  empty countdown loops are real code; separate loop variables for nested loops.
- `if (x == 0) f(0x62); else f(0x61);`: the arm order picks beqz / bnez; calling in each arm can hoist a `lui`.

**Inlined code**
- Many functions inline already-matched ones (tools/inlined.py): copy them as `static inline` helpers, several per
  function; big dispatchers are switches over such handlers (write each case out instead of a goto into a shared
  tail; a separate pointer local per case for repeated scratchpad loads). A helper returning through a local adds a
  `move`: write that body out. Scratchpad pointers and loads can be locals of a parameterless inline helper, with
  the same dead pointer locals declared in the callers.

- Dispatchers (dispatch.py): write every case in full with its helper call; where retail shares a tail between a
  case and a helper (a branch into the middle of the copy), the same code written out again is merged back by gcc
  (a00 f_HandleTownQuestRewardVisualActor matched at the first compile that way).
- Per-case pointer locals (or one per copy of an inline body) shorten live ranges and fix s-register swaps
  (regswap's fork finds them); an unexplained `move sN,sM` of the actor pointer is `u8 *b = a;` used only in the last
  call; one inline helper per constant address (a helper taking the address as a parameter loads it at the call
  site); pass the caller's pointer to a helper that would re-read a field; one parameterized inline for helpers that
  differ only in a table or argument cross-jumps like retail; a shared tail retail places after the last case is
  written in every case; nested `if (x != c) {...}` instead of an early return inside a helper stops gcc
  cross-jumping one arm between two copies.
- Collision-handler family (a04-a08 func_8010A9A8 / func_8010C8B4 adapt to all variants): a separate temporary per
  multiply, reuse dx for later locals (lim, abs value) so it gets s0, `fail:` / `ret1:` labels with gotos for the
  shared return blocks, the land tail as `static inline land(p, y)`, and the store before `return 2` with plain
  gotos (never a `ret` variable).
- `if (--S16F(a, 0x40) == 0)` (an s16 field) tests with `sll 16`; the u16 field gives `andi 0xFFFF`.

**Calls and prototypes**
- install_c drops scratch prototypes: cast arguments (`(s16)`), give callees their real return types (a void
  prototype for a value-returning callee changes scheduling; a pointer return type changes delay-slot filling).
- Leftover a1/a2 at a call: call with fewer arguments (`T f();`), or pass the extra value through a K&R prototype
  (ratan2 keeps SquareRoot0's result in a2); unused parameters passed on decide delay-slot fill; a K&R definition
  when existing callers pass fewer arguments; call through a cast function pointer when the file's prototype has
  another argument count.

**Globals, scratchpad, structs**
- Scratchpad as extern symbols (`D_1F80xxxx`), not `*(T *)0x1F80xxxx` (`lui at` vs a shared %hi), except where the
  constant address gives the right `lui` placement; base locals `s = D_1F800000;` with call arguments
  `D_1F8000D0 + 0x28` give retail's derived bases; `s32 *sp = &D_1F800084;` keeps the `lui` in a saved register.
- Base + offset of a global: a struct-typed extern (or a struct-typed alias in config/aliases_<prog>.ld) or a local
  pointer; one field through the symbol and the others through `v = &G;`; `&D[0x40]` instead of the next symbol
  re-emits the `lui`; a second buffer is its own extern, not `&buf[10]`.
- addu operand order: `a->arr[i]` / `((T *)p)->arr[i]` / `T *t = D; &t[i]` put the base first; pointer arithmetic,
  `<< 2` instead of `* 4`, or `(u16 *)(idx * 2 + (s32)tbl)` put it second.
- Struct copies from an extern reproduce local array initialisers (a local struct copy of a rodata table for a
  16-byte copy loop); lw/sw copies need an s32 member, byte structs copy with lwl/lwr.
- Locals sit at increasing stack offsets in declaration order; an unused `s32 pad[N]` fixes a frame size.
- Small forms: `if (x) call(); k = 0;` for a value set in a delay slot and again after a call; `move t0,v0` right
  after a test means the field was re-read; a scratchpad pointer set after an early return moves its `lui`; speed
  tables as u16 fields into u32 locals, `(u32)((s16)x * 19) >> 4`; a clamp with a copy `if (u >= 0x80) v = 0x80;
  else v = u;`.
- Primitives: addPrim / setaddr / setlen with `struct { unsigned addr:24; unsigned len:8; }`; `TERM_PRIM` through a
  local pointer.

**Round 8 forms**
- Two tests sharing one body where retail reloads the global in each: `if (A) {body; return;} else if (B) {body;
  return;}` with the body written twice, not `A || B`.
- Keeping the first copy of a cross-jumped call: on the first path `r = a[0x29] = call(...); test: if (r) goto found;
  goto end;`, the last path `r = a[0x29] = call(...); goto test;` (gcc otherwise keeps the later copy).
- A local whose address goes to a call stays live to the end of its block: declare a shared struct / array copy in
  the enclosing scope to reproduce retail's stack-slot reuse.
- Jump table with empty cases: distinct dead stores per case (`case 0: k = 0; break; case 1: k = 1; break;`).
- `sll/sra 16` of an argument register right before a `jal` is a cast at the call (`f((s16)z)`).
- A `u8` return type breaks implicit-int callers that test the result (ccheck OK, link DIFF): keep s32 and `return
  a[0x29];`. Check how other overlays call a callee: a wrong argument count changes scheduling.
- Depth-cued polygon lists: `__asm__ volatile("nop")` before `p->rgb2`, `*otz` stored in each arm of the max / min
  code, `mode = c >> 24; switch (mode & 3) { case 1: case 3: ...}`; the dpcs per vertex as a static inline helper.
- Global's full address hoisted to the outer loop's preheader: `g = D;` as the first statement of the outer body.
- Functions with no frame and `or t0,zero,a0` moves (gcc emits addu) are hand-written assembly: mark them, do not
  try to match them.

**Round 9 forms**
- Three scratchpad globals read in a row, retail loading all `lui`s first: pointer locals in a block `{ s16 *p0 =
  &D_1F800160; s16 *p1 = &D_1F800162; s16 *p2 = &D_1F800164; dx = *p0 - H(a,0x2E); ... }`.
- Strength-reduced pointer registers follow the order of the pointer increments at the end of the loop body and of
  their inits before the loop (not the declaration order): permlines on the init lines.
- A value stored with different constants per path: write the store with its constant in every branch.
- `__asm__ volatile("");` between statements: a scheduler barrier that emits nothing.
- Check callee argument counts against matched callers before blaming registers (m2c invents arguments; a `li a0`
  that moved into a delay slot means the call has none). An s16-returning pending callee: call it through
  `((s16 (*)(u8 *))f)(a)`.
- `u16 spd = (s8)tbl[i];` gives `lbu; sll 24; sra 24` (an s32 local gives `lb`); `s32 y0 = *(s16 *)(a + 0x156);` keeps
  `lh` (an s16 local gives `lhu`); 4-byte records walked with a counter: `e[i].f`, not `e++`; an angle stepping per
  iteration: `i * 0xC3` in the calls; `do { n++; } while (n->w != 0);` for the delay-slot increment loop.
- Nested-switch state machines: write them from the retail asm (statemachine.py drafts are broken for them):
  `tools/statemachine.py PROG NAME --cases` writes build/statemachine/<prog>/<name>.cases.txt, the retail asm cut
  per case block (cases entering it, address range, calls, the branches leaving it and where they land: `case 9`,
  `case 10 +0x1C` = a shared tail inside another case, `head`, `outside`).
- "One extra move" near misses (retail `move a0,v0` our compile folds): a copy of the value in its own local used
  by the later statements (`rr_c = rr;` right after `rr = r;`, then `if (rr_c < 0)`): regswap `keep` / `copy`
  (the rush family went 5 -> 3 words with it). A call result first stored in a local before a shift / abs:
  regswap `callcopy`.
- Loop hoisting: `tools/loophoist.py FILE.c FUNC --prog P` lists gcc's movables (cc1 -dL: insn, reg, life,
  savings, moved / not, the value) and, per loop, the constants / addresses loaded before vs inside it in ours and
  in retail. a04 func_8013C2EC: gcc 2.8.1 hoists the constants 0x55555555 / 0x5000000 / 0x2000000 (move-insn,
  savings 1, life 31-65), retail loads them inside the loop and hoists only the %hi of the three globals.

**Round 10 forms**
- NPC actor state machines (a04-a08 and likely elsewhere): case 0 init (func_800519E0 / func_80051B70 +
  func_80040CDC + a store list), case 1 dispatch on a[0x5E] / a[3] / a[5], case 2 empty, case 3 calls func_8007A624:
  write them straight from the retail asm (2-4 minutes each). Find them: `python3 -I tools/npcsm.py --list
  [PROGS]` (139 pending on 2026-11-24 over 22 programs, all with the `switch (a[4])` at the top; `--all` adds the
  other callers of func_8007A624: 306). `tools/npcsm.py PROG NAME|ALL` drafts them in the skeleton's spelling
  (m2c's draft restructured: case order 0 / 1 / 2 / 3, `break;` ends, `a[4]++`, never-assigned m2c temporaries
  replaced by the case value / the head's constant, `*(T *)0x1F80xxxx` -> the linker's `D_1F80XXXX`, a global
  read at several offsets through a `u8 *g = (u8 *)&D_X;` local) and runs permlines over the case-0 stores of a
  draft within 40 words. The drafts are a start, not matches: 1 of 139 matched (a0f func_801183C8, 6 -> 0 by
  the case-0 store permutation); 21 are within 40 words, most need hand work (retail evaluates a call's first
  argument `a + 0x2C` before the stores that precede it, an `if (init(...) != 0) break;` shape, inner switches).
- Inline flag helper: `static inline s32 f(...)` with early `return 1;` and a final `return 0;`, called as `r = f(A);
  r += f(B); if (r == 2)` (not `f(A) + f(B) == 2`, not separate r0 / r1).
- `bne v0,X; li v0,K1 (delay); li v0,K2; L: sb v0`: one store per arm, never a local assigned per arm.
- One jal reached from two arms that set different arguments: write the whole call in each arm.
- An inline helper taking a global's address hoists the address into a saved register: use a statement-expression
  macro `({ ... })`.
- `__asm__ volatile("");` right after a store retail keeps before a later independent load (wrap it in `do { } while
  (0)` if a later load then stays late).
- OT links: `*(u32 *)(ot + 0x10) = p` through a `u8 *ot` local (one per link), not `D_800ED8C8[4] = p` (an array store
  the next global load is hoisted above).
- A dead store retail keeps: `*(volatile u8 *)(a + 3) = 0;` after `a[3]++`.
- `*(s32 *)(a + (a[9] << 2) + 0xC0)` gives the base-first addu; a pointer result kept in v0 with nothing set on the NULL
  path: `if (p != NULL) { ...; return p; }` and no final return.
- One store shared by two of three values: `if (c1) k = 3; else if (c2) k = 2; else { a[x] = 1; goto done; } a[x] = k;
  done:`.
- A store in a `jal` delay slot is written before the call.

**Round 11 forms**
- Family template method: match one member, diff each sibling's opcode-normalised asm against it, map callees and
  symbols from the jal / %hi lists, substitute constants and store lists (minutes per sibling).
- A store in a jal delay slot that gcc will not move there: `MEMBER_AT(s16, a, off) = K;`.
- A pointer local reused in two places lands in a saved register: give each place its own local.
- A talk-state switch repeated with different script tables: a multi-line `#define` macro, not a static inline.
- Flag helpers: `if (A || B) return 1; return 0;` (branches); `return A || B;` gives scc.
- ccheck masks rodata: when a switch has empty cases, check the case-to-label mapping against the jtbl in
  asm/<prog>/data/*rodata*.s (a wrong one passes ccheck and fails the link).
- Compare orientation (`a > b` vs `b < a`) changes load order and registers: try both; split `x + (y + K)` into a
  local against reassociation; `(s16)(y + K) + z`.
- `n = K; a[8] = n; if (x < n)` stops gcc reusing the constant for a later store; `a[6]++` / `a[5]++` instead of `= 1`
  when retail reuses the compare constant; empty `case 2: break;` moves the decision tree's root.
- `switch ((s32)((u32)sw >> 8))` for srl + slti; a variable shift whose count is also returned: `u32 k = 1; if (x >=
  ((u32)tbl[i] >> k)) return k;`; sra instead of srl on a u8: shift by a local (`n = 2; (x >> n) & 1`).

**Round 12 forms**
- Memory CSE off: a chained assignment `H(a,0x32) = H(a,0x7C) = K;` makes later field reads real loads (retail re-reads
  a field right after storing a constant).
- Early load, late store of a counter: `f = a[4] + 1;` at the top of the block, `a[4] = f;` at its end (the `sb` lands
  in a jal delay slot); `a[4]++` does not.
- An argument saved to a frame slot (`sw a0,0x18(sp)` below the frame size): `void *arg0` + `u8 *a = arg0;`.
- `move v0,sN` with no sll/sra: the return type is s32 even when the value is stored to an s16 field.
- `s32 pad[1];` gives a leaf an 8-byte frame (`pad[2]` 16, a scalar none).
- A real `mult` by a constant: multiply by the field just stored with it (`H(a,0x2E) = 0x8E8; ... H(a,0x2E) * x`);
  a literal gives shift-add.
- Two adjacent s16 globals into fields: read both into locals first (a struct copy gives lwl/lwr); two globals
  loaded before stores into the actor: temporaries first (aliasing).
- Loop-carried `ang += K` set up after the hoisted constants: `ang + i * K`. A pointer set after the loop's entry
  test: `i = 0; if (i < n) { p = a + 0xE; do { ... } while (i < n); }`.
- Identical tails kept apart: `return 0;` in one case, `goto ret0;` in the others, `ret0: return 0;` inside the last
  case; both loops falling through to one final `return -1;` for retail's single `li v0,-1`.
- Primitive fills (POLY_G4) whose stores stay in source order: struct members, not casts; OT-link statements in
  `do { } while (0)`.
- Literal constants inside an index that gcc regroups: put them in locals (`s32 n1 = 1, n2 = 2;`).
- Which register CSE keeps after `if (r == 2)`: add a use of `r` that folds away (`t + r - 2`).
- `case 0: break;` below the lowest label moves gcc's switch pivot.
- A temporary written as one expression (`s = (rand() * rand() >> 16) + K`) gets a higher priority than two
  statements (s0 / s1 swap).
- Compare orientation swaps registers: `S(a,x) > S(c,y) + K` vs `S(c,y) + K < S(a,x)`; `if (D_X <= e)` loads the
  global first; a `li vN,K` in a delay slot may be the other compare's constant (`a[3] == 3`, not 2).
- A load retail puts before a store into a jal delay slot: write that copy statement first.
- Global arrays `D_X[7] = ...` rather than a pointer local (gcc hoists the pointer above the previous store); a
  struct member `D_800BF870.pad1[0x197]` vs a pointer cast choose the `lui` / `addiu` registers.
- An inlined helper taking a table: a `#define` macro keeps the address load in place (a static inline loads it
  early). A repeated null test after a guarded copy: a static inline returning the pointer.
- Case tails merged where retail merges: per-case locals (`r = 0x28; h = 0x50;`) so the tail instructions are equal;
  write each case's tail in full and let gcc cross-jump; a trailing store skipped by early branches goes into each
  arm.
- Loop-hoist threshold in loops with calls (contact dispatchers): gcc moves an invariant when threshold (~26) x
  savings x lifetime >= the loop's insn count; a jump-table address (156) is on the edge. A constant assigned through
  a variable set in two places (`k = 2;` / `k = 1;`) is not movable and keeps the jump table in the loop; a `u16 d`
  temporary per arm changes the insn count (loophoist.py).
- Contact-dispatch loops: `D_1F800182 = n; while (D_1F800182) { b = *l; D_1F800182--; l++; if (b[0] & 1) switch
  (b[2]) ... }`, the case map from statemachine.py plus the table offset; cases equal to matched functions as static
  inline helpers (take regswap's double `do { } while (0)` wraps).
- One parameter masked twice: `(m & 0xFF)` in the test and `(u8)m` as the argument; `if (r[3] == 0)` after
  `r[3] = a1` reproduces the `andi` of the argument register; `parts[a[9] - 1]` keeps `addiu -1` only through a
  struct with `u8 *parts[2]`.
- A random choice of an argument: two full calls in if / else (a ternary gives the delay-slot overwrite form).
- A scratch `extern u8 D_800BF870;` clashes with include/game.h's GameState: include game.h and use its member.
- Writing straight from the retail asm beat the drafts this round (12 of a00's 21 matches first or second try).

**Round 13 forms**
- Write new functions straight from the retail asm (round 13: 79 functions, most first or second compile); run
  regswap early in the background on anything under ~35 words off (it closed two from 33 and 7 words).
- Matched callees work unchanged as `static inline` helpers inside dispatchers (a00's 16-case town-creature
  dispatcher, 0xF28, second try). A helper whose result is tested: early `return 0`s, `break` where the return sits
  after the switch, an explicit `default: return 0;`; a result tested through `sll 16`: cast every call `(s16)`.
- Leftover argument registers: a1 / a2 set before a `jal` whose callee other callers call with fewer arguments are
  leftovers; call it with fewer arguments.
- `__builtin_abs(x)` is one insn (`bgez; move; negu` or `bgez; nop; negu`): loads and stores are scheduled across it;
  `if (x < 0) x = -x;` is a branch that splits the block; `abs()` gives `bgez; nop; negu`.
- Keep retail's `move` copy: a narrow copy (`u16 b = ang;`); gcc coalesces an s32 copy, not a zero-extend.
- `H *= -1` (or via an s32 temporary) loads with `lh`, `H = -H` with `lhu`; `(s16)(U(a,0x40) & 0xFF) < 0xA` gives
  `slti`, without the cast `sltiu`.
- A comparison re-tested in an else-if (no jump threading): swap the operands of the second test.
- Range compares: `!(x >= 0xC && x <= 0x1C)` gives `addiu; sltiu; xori`; range cases first (`case 0x5A ... 0x5C:`)
  for retail's beq / slt / slti tree; falling off the end with no return returns the compare result left in v0.
- A dead store retail keeps (`H50 = 0; ... H50 = -0xE;`): gcc drops the first only when adjacent; put an unrelated
  store between them.
- `u8 r` keeps a separate `move v0,zero` when gcc would merge `return 0` into `return r`.
- Hidden extra local: `if (t != -1) k = t; else ...` gives the `move sN,vN` in a delay slot.
- Shared "deny" tail: write it inside the first if (`deny: if (mode == 1) return 1; return 4;`) and `goto deny`;
  a test reached by `j` with the constant in the delay slot: set the constant per branch and test once.
- Table base before the index arithmetic: `e = (u8 *)TABLE; e += k * 3;` (`TABLE[k]` multiplies first).
- Load-delay nops in retail mean source order: field copies before the constant stores.
- A stack-slot local in a leaf (`sw t2,0(sp)` / `lw`, 8-byte frame) is a `volatile s32`.
- Scratchpad: `u8 *t = (u8 *)0x1F800000;` + offsets gives `lui` with no `ori`; a literal `*(u32 *)0x1F800004 = x`
  the `lui at` macro store; an extern struct `lui` + `addiu`. GTE scratch globals as pointer locals
  (`s32 *otz = &D_1F800080;`); regswap `ptrlocal` `{ s32 *p = &D_1F800088; a = *p; }` for a `lui t0`.
- Narrow types fix registers: u8 colour parameters, a u16 quotient, `u8 k` keys, an `s16` local holding constants
  compared with a call result, `s16 mode` parameter (moves its copy after the zero inits).
- Wraps and scopes steer priorities: `do { } while (0)` around statements using a GTE scratch pointer raises it;
  block-scoped temporaries per arm lower one; one temporary per branch for callee-saved choices; two scratchpad
  globals with both `lui`s first: block-scoped s32 locals.
- gcc 2.8 aliasing: a first store written as a struct member keeps struct-member loads before it (a scalar `*p` /
  `p[0]` store lets them pass); `*t` loads never pass a store.
- Index loop `i = cell; do { k = list[i]; ... } while (list[++i] != 0xFFFF);` gives retail's preheader order (a
  pointer walk puts the giv init before the hoisted invariants); index through the array at the field offset
  (`((u8 **)(p + 0xC0))[i]`); morph loops: a goto loop over a pointer biased to the record's end (`d[-8]`).
- One field set to different values per arm: the store in each arm (gcc merges into one `sh`, value in v0);
  `f(a, 0)` / `f(a, 1)` in both arms for `move a0,s0` in the delay slot; an `or` reusing a call's constant argument
  register: put it after the call; `H(a,0x42)++; f(.., H(a,0x42));` rather than `++H` in the arguments.
- Min / max of three: `e = b;` in each arm and `b = e;` after; write each arm of an offset chain in full.
- A shift operand as a temporary first (`w = pl[3] << 12; y = (a*x + c*z + w) / -pl[1];`) for local-alloc ties.
- Bytes past the end of GameState: `u8 *g = (u8 *)&D_800BF870; g[0x5E5]`.
- Families seen this round: the ColTri collision floor searches (a02 func_801258A4 / func_80125F7C -> a0k, a07; a
  table choice on D_800BF816), the 6-copy func_8010AFB4 / func_801253A8 family, GT3 / GT4 UV-scroll and depth-cued
  list builders; Tomba state handlers (callers of func_80056B48 / func_80055D5C / func_8005444C / func_800551C4) are
  quick from the asm.

**Round 14 forms**
- Big two-table state machines are quick from `statemachine.py PROG NAME --cases` (a0a's 0xD04 evil-pig state machine
  in ~10 compiles), then `nearcopy.py <progs> --install` for its exact copies (5 more, 20 KB).
- Skeleton families copy-edit in 1-2 minutes per member: the evil-pig attack / intro functions of a0a..a0f, the
  streamed-audio range tables (a02 f_UpdateTabbyHouseResidentActor; a jump table whose cases only load a table, n and
  base then jump to a common tail: generated from the asm by a script, 7 copies in a00..a08), the a08 Tomba water code
  (shared `snap_inl` / `swim_inl` / `push_inl` / `near_inl` helpers), the a00 barrel / drying-rack chain. nearcopy
  `--near` "extra block": try deleting that if-block from the source C.
- Cross-jumping runs before sched2: to keep two copies of an identical arm, write one arm's statements in another
  order; for one shared store at the join, end every arm with the same field store; `lui; addiu` of a table in each
  arm means the table use was written in both arms.
- `a[5]++` / `a[6]++` in a case whose value is known reuses the switch tree's compare register (regswap `caseinc`).
- Switch on {0,1} with retail's `beq 1; slti 2; beqz; bnez`: add an empty `case 2: break;`.
- `x < 7 || x >= 0x13` on one byte folds into a range test; nested ifs keep two `sltiu`.
- Unused local arrays size the frame: `s32 pad[4];` -> 0x30, `s32 pad[8];` for a leaf with `addiu sp,-32`, `s16 v[6]`.
- One pointer local per use site of a global (`g`, `g2`, `g3`; not one local assigned twice): retail's repeated
  `lui` / `addiu`, lower priority.
- MEMBER_AT stores let global / scratchpad loads move above them; `MEMBER_AT(u8 *, t, 0xD0)` reloads a pointer field
  after every store through the other pointer; `D[k].field` on an own struct over an alias symbol keeps `lw 4(v1)`
  (a cast folds the +4 into %lo).
- Typed parts struct parameter (`typedef struct { u8 pad[0xC0]; u8 *parts[1]; } AreaPartsOwner;`): `a->parts[i]`
  gives `addu rX, a, idx` (casts give `idx, a`); keep index arithmetic out of the offset (`parts[i + 1]`,
  `j = a[8] - 1; parts[j]`, `k = (i - 1) * 4; k--;`); `q = a; q += i * 4;` for base-first addu.
- Flags tested through a `move v0,sN` copy are s16.
- A constant kept in a register for `mult`: `s = K; s = (x * s) >> 8;`, or a variable later reused for another value.
- Callee-saved order through global-alloc priority: `x = A; x += B;` adds refs.
- `__builtin_abs` + narrow copy for a `move a1,v0`: `s32 m = __builtin_abs(t) + 0x20; s16 k = m;`.
- Boolean argument from a masked bit: `k = x & 0x100; f(a, k != 0);` (`andi; sltu`); direct gives `srl; andi 1`.
- After `bne` proves a register equals a constant, CSE stores that register: write the constant.
- Store-flag conversion (`if (x & bit) return 0; return 1;` -> `sltiu`): `__asm__ volatile("")` before `return 1`
  keeps the branch; a bit test needs `bit = 1 << i` in a variable.
- Shared return blocks: `goto ret1` / `goto ret0` / `goto ret2` to final labels; a tri-state result: `r = 0` in the
  else arm, not as an initial value; a 1/0 flag set in a delay slot and tested after an init block is an inlined
  helper's return.
- A void function whose caller returns its value: keep it void and cast at the caller (s32 changes delay-slot
  filling).
- CD callback flags are volatile (D_800BE0E0 / E6 / E8 / EA), except where a store must follow a volatile load
  (Round 15 forms).
- A loop over a struct table `D[i].x` gives one induction variable (`p++` gives two); keep `(a - b) + (c + K)` with
  casts `(s16)(a - b) + (u16)(c + K)`; `lui; subu`: `k = 0x1400; H50 = k; W30 -= k << 8;`.
- If / else `j` layout: `if (!A && !B && !C) x = 6; else x = 5;`.
- A table byte loaded `lbu; sll; sra`: u8 table, `s16 x = (s8)p[1]`.
- Two retail copies of a block are two source copies (do not share a case).
- A dead store retail keeps on a stack slot: permlines over the statements.

**Round 15 forms**
- Tomba state handlers (MAIN 0x80062000-0x80068000; overlay callers of func_80056B48 / func_80055D5C / func_8005444C /
  func_800551C4) take about 2 minutes each from the asm.
- A pending function can be an exact case body of a matched dispatcher (a04 func_80111260 = case 1 of func_801103F0),
  or a matched function with another divisor (`magicdiv.py`: a0e func_801117CC = a04 func_8013C2EC with /500).
- Loads through another pointer (a table entry, an escaped stack array, a scratchpad global) cannot move above a store
  through the actor pointer: when retail loads early, put the load right after the store it follows, or compute into
  locals before the stores. MEMBER_AT on the one access (regswap `member`) lets global loads pass actor stores; a
  MEMBER_AT store of a function pointer likewise.
- A volatile store cannot pass a volatile load: in MAIN func_8001D7C4 D_800BE0E0 is not volatile (its store follows
  the volatile D_1F8001F4 load) while D_800BE0E6 / E8 / EA are. A volatile second read keeps a reload CSE would merge.
- One value per arm (`if (x == 0) v = A; else if (x == 1) v = B; else v = x;`): an initial `v = A;` is hoisted to the
  function top. Same constant into two fields: the stores in each arm (gcc cross-jumps the shared `sh`).
- Narrow copies keep `move`s: `u16 kk = k;` before two masks of an s32; `s16 b = ...; s16 n = b; if (..) n = b + 1;`.
- `k2 = *(s16 *)(t + 0x58) = h;` folds a field write into an assignment (regswap `chain`); chained stores store the
  rightmost first; `H(b,0xBA) = U(b,0xB8); H(b,0xBC) = U(b,0xB8);` gives `move v1,v0`.
- Testing a field just masked: `U78 &= 0xFFFB; if (H(a,0x78) & 0x8000)` (signed re-read tests the stored value).
- `return;` in a non-void function: a branch straight to the epilogue with garbage in v0; an uninitialised local on a
  default path reads the leftover argument register.
- `or` operand order: a named s16 local declared first (`m = H & ~0xFF; n = m | lo;`); clamp with a move:
  `s16 lo = H & 0xFF; if (lo >= 0x80) lo = 0x80;`; colour words with the constant first.
- Angle wrap with three registers: `s16 dd = t - FU16(q,0x14); if (dd < -0x800) dd += 0x1000; else if (dd > 0x800)
  dd -= 0x1000;` with `dd = (t = f()) - x;`.
- Undo constant folding: `d - K` in a block-scoped temporary, the constant in a local (`o = 0x6E`), `x - (h + 0xC8)`
  for `addu; addiu -200; subu`.
- A derived base (`addiu s0,s2,-0x146`): `rec = (u16 *)((u8 *)&D_800BF870 + 0x146)` for the writes, `gs` assigned
  after it for the reads; GameState byte flags per arm `{ u8 *g = (u8 *)&D_800BF870; g[0x162] |= 1 << n; }`.
- GTE inline stores: one asm string `"addu $12,%0,$0; swc2 $12,8($12); ..."` with clobbers $12-$15 and memory
  (maspsx rejects `move` in a multi-insn string); four nops around rtpt as a custom asm with `.word 0x4A280030`.
- Packet walk around a call: `p += 6; q = p; ...; q += 3; p = q;` (stops a giv); packet constants stay in the loop
  when the OT-link stores are in `do { } while (0)`.
- Scratchpad matrix pointers in loops: assign them inside the loop body (loop.c hoists them as retail did);
  D_1F800020 is its own symbol, not `D_1F800000 + 0x20`. The same scratchpad word read as u8 and written as u16: one
  u16 symbol plus `*(u8 *)&SYM`.
- Grid row loops: a static inline row helper `p = *(s16 **)(a + 0xC); p += 2; p += xs * H + y; for (; xs <= xe;
  xs++) { ...; p += H; }` with no block-scoped local in the loop.
- `bnez` delay slot filled from the target where retail has the fall-through: `__asm__ volatile("");` before the
  target statement; store flag kept as `beq`: `if (x == 3) return 1; __asm__ volatile(""); return 0;`.
- Open pattern (5 spawners, ~5 KB: a05 f_SpawnKujaraSummitSceneActorsFromPlacementTable, a04 f_SpawnKujaraRanch...,
  a07 f_SpawnCircus..., a01 f_SpawnPipeArea...): retail keeps one `lui %hi(D_800BF870)` in a saved register for both
  `h = &D_800BF870` and an in-loop direct `lbu %lo(D_800BF870)(sN)`; ours re-does the lui in the loop.
- Splat can leave a jump table as raw `.word` data (a02 D_801092FC): declare it `jtbl_XXXXXXXX = 0x...; //
  type:jtbl` in config/symbol_addrs_<prog>.txt and re-split; a pending "function" with no prologue that uses saved
  registers is a split-off tail (a02 func_8010CF30 of func_8010C8E4: merge in the config).

**Round 16 forms** (agents on Fable; ~100 KB, the best round)
- Shared-lui spawners (the open pattern of round 15, solved): either assign both base pointers as the first
  statements inside the loop body (`do { h = (u8 *)&D_800BF870; g = D_800BF808; ...`: both are needed, h alone is
  one insn short of loop.c's threshold), or use no h / g variable at all and reach the globals through
  `static inline u8 *GS(void) { return (u8 *)&D_800BF870; }` / `GB()` accessors: each use is a fresh block-local
  pseudo loop.c may move, combine_movables merges them, CSE shares the lui with the direct `D_800BF870.unk0` read.
  A generator from the a04 agent's template is in the session scratchpad r16b/a04/gen.py. Left: a00
  f_SpawnFishermensTownActorsFromPlacementTable, a01 f_SpawnPipeAreaSceneActorsFromPlacementTable, a0k
  f_SpawnTinyMouseVillageActorsFromPlacementTable.
- gcc 2.8.1's scheduler (cc1 `-dS -dR`, x.i.sched2): in a call-free block every insn has priority 1, the ready list
  is taken last-luid-first, a store jumps ahead of a non-memory insn, a load waits one cycle after a store. Floating
  stores (zero, a saved register, a long-lived constant) sink below the `li v0; sh v0` chain in source order; a
  floating `li` lands where its luid falls, so retail's position gives the source position of that constant's
  first use. Local-alloc ties go to the first-born; move floating stores to flip them.
- The 0x500 skeleton fix: the second store of a constant after another constant store (not chained). Two `li` of
  one constant plus a real `mult`: `s32 h = 0x8E8; h = (a[0x11] * h) / 144;`.
- `do { } while (0)` doubles the ref counts inside it (refs weighted by loop depth): wrap only the computation that
  must rank higher; loop notes are scheduling barriers (the first insn after a LOOP_BEG note stays first; a
  division by 16 right after `do {` gets the duplicated `bgez; sra` shape). regswap's wraps work through this.
- Local-alloc gives v0 to the highest refs x log2(refs) / lifetime in the order sched1 left (ties: first born): load
  order through an inline helper with s32 parameters.
- Cross-jumping keeps the last copy: when retail keeps the first and later cases jump back into it, write the code
  once with labels and `goto` from the later cases; an inner switch's last `if (c) break; goto next;` gets inverted:
  write that `break` as a goto.
- Opaque copies (hacks, rank last): `__asm__("" : "=r"(p2) : "0"(a));` for stores through the call's a0 across a
  loop end, `__asm__("" : "=r"(n) : "0"(1));` for a constant barrier; `__asm__ volatile("");` first in an else arm
  keeps an if / else constant from being hoisted (`beqz; j; li v0,A; L: li v0,B`).
- `lh; sra K` of an s16 field: gcc 2.8.1 narrows `H >> K` to `lhu; sll 16; sra 16+K`; retail's `lh; sra 6` is
  `(H * 0x40) >> 12`. `v = (F * 4) >> 3` keeps a reload where `F >> 1` forwards the stored register.
- Byte constant through an s32 local (`n = 4; a[0xD] = n; tbl = base + n;`) for post-reload CSE in SImode.
- A store or call in every arm instead of a join variable (raises the base's refs; gcc cross-jumps them back).
- Camera-zone functions (callers of func_8006E3F4 / func_8006CEC4 with D_1F8000D0, 11 matched): a block-scoped
  `s16 *c = D_1F8000D0;` per arm, `pos` as `struct { s16 xl, x, yl, y, zl, z; }` in x, y, z order, each Pos
  block-scoped per sp slot. Left: a00 f_UpdateA00InteriorCamera, f_UpdateFishermensTownCamera, a01 func_8010AE30,
  func_8010AF6C, a02 func_80115F58, a09 func_80109D04, a0c func_8010D2D8, a0f func_8010BE48.
- Typed post-increment keeps a copy: `p = (u8 *)(*(DrMode12 **)&D_800BF544)++;`.
- GTE depth cue: a macro `{ u32 *q = &p->rgb0; lddp(..); ldrgb(p->rgb0); dpcs(); strgb(q); }` (an inline function
  makes loop.c hoist the pointers); a01's GT3 / GT4 list builders are C (func_80132690 was an ASM-by-design
  candidate).
- `if (!(flag & 0x80000000))` instead of `flag >= 0` lengthens the constant's life (hoisted, re-loaded at uses).
- Shared tails read from a label-stripped listing are often wrong: write the obvious form, then follow ccheck's
  one-word `beq +0xNN` diff to the real target.
- Byte-aligned struct copy from an extern (`typedef struct { u8 v[0x30]; } T; T tbl = D_X;`): the lwl / lwr loop.
- Target prototypes still apply at install: copy the callee's real narrow-parameter prototypes into the scratch.

**Round 17 forms**
- GT3 / GT4 list builders with flg / otz at D_1F800080 / 84 (a04..a08 and a01 families, with their dispatchers
  `gte_SetRotMatrix(&D_1F8000F8)` + one loop per arm): `u32 m = 0xFFF0F0F0;` as a local; `c >>= 24; mode = c & 3;`;
  `*otz = b >> 2;` inside every min / max arm (more refs, cross-jumping merges them); `do { e = *otz >> 10; *otz =
  ...; } while (0);`; UV scroll `if (c & 8) { u32 u = D_8014A450 >> 4; *(u8 *)&p->uvN += u; }`; skip tests with
  `goto next`; own locals per arm in the dispatcher, `w >>= 16;` between the two calls, `m = tbl + *i` with `u32 *tbl`.
- Dispatchers and handler tails (the 60-case Tomba dispatchers): write the shared tails in full in every case
  (cross-jumping after sched1 merges them as retail did); a goto only where retail jumps into the middle of another
  case or onto the call itself.
- CSE forgets an actor field once another byte field is stored (`a[7] = 2; a[6]++;` reloads a[6]); compute a value
  into a local before an intervening store to force a reload. `if (x == K) m = 0; else m = f();` stops CSE carrying K
  into a saved register (`m = 0; if (x != K) m = f();` does).
- A register named by an argument: a value kept in a2 / a3 up to a call is that call's extra argument (pass it; a
  global passed as an extra argument to a K&R callee and read through `D_800BF870.pad1[..]` reuses a3).
- `__builtin_abs(H)` on an `lh` value in the same register gives the always-negating `bgez v0; negu v0`.
- Camera-zone tables: a pointer local declared before the D_800BF808 pointer (lui order = declaration order);
  `V3 *t = &T[g[0xF]]` uses one index, direct `T[..].x/.y/.z` reloads it for z; the `== 2` arm and the else arm each
  get their full func_8006E3F4 / func_8006CEC4 code but share one function-scope `pos`.
- An index scaled after its subtraction (`addiu -5; sll`): pass it through `static inline s32 Idx5(u8 *g) { return
  g[0xF] - 5; }` (RTL inlining hides the PLUS from the tree folder); `static inline s32 Sub250(s32 m) { return m -
  0xFA; }` likewise stops `S30 - (m - 0xFA)` becoming `(S30 + 0xFA) - m`.
- A full scratchpad address kept in a saved register and shared with an inlined helper: assign the pointer as its own
  statement after the call.
- Keeping the parameter out of a0: a block-scoped local loaded early and stored last lands in a0.
- Two-byte table entries: `struct { u8 m, k; } T[]; T[a[3]].k`.
- `case 3: default:` moves gcc's case-tree pivot; an empty `case 2: break;` after `case 0:` falling into `case 1:`
  gives the `beq 1; slti 2; beqz; bnez` tree.
- Spawners without mode (a0k): the GS() / GB() accessors also stop the 0xFF constant being hoisted. All spawners are
  matched now.
- Do-while with a return inside: `continue; ret1: return 1;` at the end of the body puts the return block before the
  loop test.

**Switch and jump-table shapes (more)**
- Duplicate the cases with identical code to get a jump table whose entries share a target (gcc builds the table,
  then cross-jumps the blocks); `case 1: d = X; break; case 2: d = X; break; default: d = X;` gives separate tree
  nodes where `case 1: case 2: default:` merges them into a range; `case 0 ... 1: break; case 2 ... 3:` for the
  `bltz; slti 2; slti 4` tree; an empty `case 0: break;` keeps a `slti 2` tree; a `switch` instead of `x == K1 ||
  x == K2` in an inner loop hoists the compare constants; `break` to the final `return 0` vs an explicit `return 0`
  per case decides where v0 is set; `& 0x80` after the if/else (not in each arm) lets gcc cross-jump call tails;
  retail hoisting `move a0` above an if/else with `li a1` in each arm: the whole call in both arms.

**More forms**
- Division by a field just stored: `a->40 = K; a->4A = (...) / a->40; a->4C = (...) / a->40;` gives `li K; div`
  and the `lh` reloads (MEMBER_AT stores when the expressions read scalar globals).
- A constant from the switch dispatch reused in a shared tail: write the tail in each branch (cross-jumping merges the
  copies); a constant rematerialised after an if: `if (c) x = A; else x = B;` with the store in both arms.
- Each copy of a repeated inner loop in its own block with its own locals; gcc will not merge an arm with another
  case's identical code, so retail's branch into another case's arm is a `goto` to a label inside it; `goto ret0;`
  into `case K: ret0: return 0;` places a shared return-0 block in the middle of the switch; a `common:` label inside
  the switch with its own pointer local for a tail shared by two cases.
- Two identical tests retail keeps apart: read one through `*(volatile u8 *)&D`; nested ifs keep two compares where
  `&&` folds them; an inner switch on `x & 0xF00` gives a balanced tree, retail's linear chain is an if / else if
  chain on `k = x & 0xF00`.
- Shifting when a product is computed (`t = (rsin * k) >> 12`) places the temporary like retail; drop m2c's extra
  call arguments until stray `li`s disappear; a block-scoped table pointer `{ T *tb = D; f(a, &tb[5]); }` keeps a
  separate `addiu +off`; camera-script tables are 12-byte entries (`&T[H(a, 0x6A)++]`).
- `h = *(volatile u16 *)(a + 0x68);` keeps a single lhu with `(s16)h` as sll/sra; `*(volatile s16 *)&G = 1;`
  keeps a store out of a jump delay slot; `u8 c = a[5]--; if (c == 0)` for `addiu v1,v0,255; andi`; a loop counter
  `n = 0x800000; ... if (--n == 0)` (splat names the constant D_7FFFFF); `(s16)(x + K)` stops reassociation; `u32 k`
  for a u8 that is both compared and passed on; a field read twice gives the CSE `move a2,v1` a local does not; a
  store through a pointer local (`p = a->10; p[0] = 1;`) changes the constant's register; `v = 0x34800; d = ...;
  v = v / d;` loads the dividend first; `s16 k = (u32)(f() - 7) < 3` drops a copy; a code label used as a callback
  value needs an alias line (`.L80117FA4 = 0x80117FA4;` in config/aliases_<prog>.ld).
- Load order of `lh 4A; lw 30; lhu 4A; lhu 50`: `*(s32 *)(a + 0x30) += H(a,0x4A) << 8; n = H(a,0x4A) +
  H(a,0x50); H(a,0x4A) = n;`; `h - i * 20` (a giv) instead of a user variable `k += 20` fixes spilled stack-slot
  order; `s32 *z = (s32 *)D_1F800090;` declared at the start of a section gives the early `lui`; accesses sharing
  `lui 0x1F80` come from `u8 *s = (u8 *)0x1F800000;`.
- Library: a pointer to a field with the others at negative offsets (`volatile s32 *t = &G.f; t[-k]`) for a
  hoisted field address; `p -= n` to re-derive the base; a block-scoped `{ volatile T *p = &G; ... }` keeps the base
  in a register across the field stores; 4.4 libcd ReadAttr layout in STATUS 2026-11-23.

**GTE**
- `gte_ldfcdir(0,0,0)` for the "handwritten" functions starting `addu t0,zero,zero; ... ctc2 t0..t2,$21..$23`;
  offset macros `gte_ldv3c` / `gte_stsxy3_g3`; DQA/DQB loads with custom asm (`ctc2 %0,$27`); draw loops with
  private macros (command word without nops, packed vertex loads, one `swc2` per SZ) and scratchpad pointers as
  locals (`s32 *flg = (s32 *)0x1F800000`).
- Reload spill registers (the asm's base pointers in GTE functions) are the call-clobbered registers no pseudo uses,
  in order: make the rest of the function allocate retail's registers and the spill cycle follows (keep a value in
  the call's a0 instead of re-reading it; compute call arguments into locals before a store so it lands in the jal
  delay slot). A pointer local with no register is rematerialised at its use; to stop two pointers to one address
  being CSE'd, give one an alias symbol.

## Tool pitfalls (open ones are listed in STATUS)

- dispatch.py wrote a helper twice when another helper needed it (fixed 2026-11-23: written once, with the
  declarations); a crash on one function no longer stops the others. For state machines use statemachine.py.
- regswap rewrites can produce invalid or semantically wrong C (MEMBER_AT with a variable offset, a reused variable
  read after its reassignment): check every result before installing. Since 2026-11-24 (6) fork never starts at
  an assignment that reads the variable or sits in a block the later uses are outside of, and the `const` kind
  (constants pulled into early locals, a hack) runs only with `--hacks` or an explicit `--only`.
- ccheck compiles a scratch with prototypes a second time with them dropped (as install_c installs it) and warns
  `install_c will produce different code` when the bytes differ (`--skip-protos-check` turns it off). install_c
  turns a scratch prototype with a parameter narrower than int (u8 / s16) into K&R `T f();` when the target calls
  that callee elsewhere (drops it when the target declares it), puts typedefs before prototypes, and on a link
  DIFF prints the first differing address as `FUNC+0xOFF` (from build/<prog>.map).
- permlines never moves a marked line past a `break;` / `return` / `continue;` / `goto` (it used to report dead
  code after a return as an improvement).
- prio.py names pseudos by declaration order even when array locals are not pseudos (names shifted).
- install_c: an existing caller with another argument count after the definition is rewritten as a call through a
  cast, `((RET (*)())f)(...)` (same `jal`, same promotions as the undeclared call it was; since 2026-11-24); alias renames are
  not applied inside moved helpers; a moved helper loses prototypes declared further down (declare them in the
  helper's block). `extern M2C_UNK func_X;` for a function the C calls becomes `s32 func_X();` (dropped when the
  target declares it) since 2026-11-23.
- regswap's member toggle only takes `name + literal` / `a->b + literal` bases (a variable offset never becomes
  MEMBER_AT, 2026-11-23); the reused / forked variable check is still by hand.
- nearcopy `--near` alone implies `--ratio 0.8` (other lengths too).
- ccheck compares jump tables since 2026-11-24 (9): a `DIFF ..., code equal, jump table differs` is a wrong
  case-to-label mapping (an empty case: `case K: break;` vs joined with the next case, or two labels swapped);
  it also warns when a scratch declares a function of the program / main with another return type or as data.
- sibling.py `store+` writes `*(T *)(base + 0xOFF) = K;` with the base of a neighbouring C store; tidy the forms
  by hand (an `a[0xB]` style) before or after install if wanted; nothing it writes is semantically checked beyond
  the bytes.
- statemachine.py's header and m2c's prototypes (`M2C_UNK f(M2C_UNK, ...)`) go into src/ with the install: delete
  the header from the scratch first; use the target's array declarations (`D_800E7E80`, not `&D_800E7E80` with a
  new extern, which makes an alias).
- variants.py writes `//--` separators: never leave them in src/. In `--set` values write `\&` and `\|`.
- permlines keeps `//P` lines in their own block and case segment since 2026-11-24 (4) (it used to move them out
  of their switch case); it prints a progress line per batch and every 15 s, `--max-seconds S` stops it.
- regswap's splits through a narrower temporary than the store's target are left out since 2026-11-24 (`--narrowing`
  tries them, flagged NARROWING); its `__typeof__` locals must not reach src/. New kinds `callres` (a call result
  through a dead local; the dead check is a forward scan, check loops) and `abs` (abs() <-> ternaries); wrap and
  volatile come first in every round, past --max-cands every kind gets its turn; `--max-seconds S` time-boxes it.
- Copy the target file's prototypes into a scratch: a different scratch prototype can pass ccheck and fail the
  link. ccheck `--no-protos` compiles the scratch the way install_c drops prototypes (fixed 2026-11-24: it lost the
  newlines after the `#include` lines and the `// CC` set-up comments).
- install_c renames a scratch macro the target defines with another body (`H` -> `H_xxxx`, with a warning; since
  2026-11-24); unique macro names per function are still clearer. On a failed linked build it prints the compiler's
  or the linker's first error lines (the NOT INSTALLED reason is the first one); it says when it changed
  config/aliases_<prog>.ld (commit it with the C); a type left defined twice by an install keeps its first copy.
- Never `pkill -f`, even with a narrow pattern: kill by PID.
- install_c copies scratch prototypes with parameter types narrower than int into the target, which changes other
  callers' code (link DIFF while ccheck is OK); it drops prototypes of callees the target does not declare (implicit
  int: cast their results, e.g. `(s16)`). Run `ccheck --no-protos` before installing; drop narrow prototypes and cast
  at the call instead.
- Write scratch files containing inline asm (`$24`, `$6`) with a quoted heredoc (`<<'EOF'`): an unquoted one expands
  them.
- `nearcopy.py --near --ratio 0.6` then hand edits of the differing constants / statements was the most productive
  method of round 8. Each near file's `// retail diff:` line (2026-11-24) says what to edit: `constants
  only`, an extra / missing block at +off, register changes, other callees.
- workqueue.py reads the pending set fresh from src/ on every run (under a second): rerun it rather than reading an
  old build/queue_*.csv.
- The container can restart in the middle of a round: commit every function or two (the disk survives, uncommitted
  work and the report do not).
- `register ... asm("reg")` matches are not installed (compiler-specific); they stay near misses.
- A static inline helper must be defined before its first use, or gcc emits it as a function.
- nearcopy refuses or mis-patches some copies (a repeated immediate, constants in helpers, callee names that differ
  per overlay): patch by hand and check the alias lines.
- inlined.py writes build/inlined_<progs>.csv for a scope (build/inlined.csv only for a run over all programs).
- dispatch.py skeletons lose the code at a label inside an inlined span that other code jumps to (gcc cross-jumped
  a tail, or a case enters the copy): the header lists those labels; write that code out in full from the plain
  decomp.py draft (gcc merges the identical tails again).
- regswap `pathsplit` / `fork` / `copy` rename locals: check a result for a variable used before it is set (an
  uninitialised read can happen to get the right register).
- install_c (2026-11-24 (4)): comma-separated externs are split before the clash check; scratch static helpers
  no installed function calls are left out; a scratch prototype of a callee with a non-int return (pointer, s16,
  u8, ...) the target does not declare is kept, K&R (`u8 *f();`); `#include "actor.h"` is carried; calls of a
  function the target defines (or prototypes) earlier with another parameter count go through the
  `((RET (*)())f)(...)` cast. ccheck warns `line N calls F with K argument(s); its definition in src/... has M`
  (the target's and main.c's definitions), and for another length prints `score N` (the aligned count that
  regswap / variants / permlines use) next to the positional count.
- regswap kinds since 2026-11-24 (4): `copy` (one use) / `keep` (every later use, or all but the first) only where
  the copy dominates the use (same block or deeper, no label / case / reassignment between, no loop back edge
  bringing another value); `callcopy` (a call inside an expression into a local, top-level or block-scoped);
  `barrier` (`__asm__ volatile("");` between two statements); `swapif` (`if (!(c)) {B} else {A}`); `perbranch`
  (the use after an if / else put into both arms with each arm's value, the local gone); `ptrlocal` (globals
  through pointer locals in a block, for runs of 1-4 statements or a whole case). Multi-declarator lines
  (`s32 a, b;`) count as locals now (they used to stop the declaration scan, so most kinds saw no locals).
- regswap kinds since 2026-11-26 (the round-12 recipes; clean kinds are tried before the hack kinds `const`,
  `volatile`, `vstore`, `barrier`, `varshift`, `twoset`, `idxlocal`, `copyback`, and win a tie): `cmpflip` (one
  comparison of a condition with its operands swapped, `x < K` <-> `x <= K - 1`), `varshift` (`x >> K` ->
  `n = K; x >> n`), `chain` (two adjacent stores of one value as `A = B = K;`), `latestore` (`x++` of a memory
  lvalue as `t = x + 1;` one to five statements above and `x = t;` in its place), `paramcopy` (a pointer
  parameter received as `void *` and copied into the typed local, a narrow one as s32), `foldeduse` (in `if (V ==
  K) {`, a K written as V, or `E + V - K`), `oneexpr` (`v = E;` merged into its one next use), `blockscope` (a
  local declared in the innermost block holding its uses, or one local per block when the uses sit in disjoint
  blocks), `twoset` (a literal in a loop through a variable set at the top and just before the use: not
  loop-movable), `accum` (`v += K` in a counted loop -> `v + i * K`), `idxlocal` (a literal inside an index as a
  local), `copyback` (a parameter used through a copy up to a later use, then copied back), `retshape` (the
  return structure: a `return X;` as a goto to the final `return X;`, identical returns sharing one label at each
  of them in turn, `if (c) { ...; return X; } REST; return X;` as an if / else falling through), `intoarms` (the
  statement after an if / else copied into both arms: undoes a cross-jump). Over the 41 round-11 / 12 near misses
  (2026-11-26) they closed none alone; `intoarms` took a01 func_8010EFBC from 8 to 4 and cmpflip + varshift a02
  func_8010FFF4 from 15 to 12. tools/loophoist.py prints the move_movables() arithmetic per movable (`s*l`,
  `need T>=X`, `edge +/-N insns`, the lifetime it would need) and the threshold bounds the file's fates imply.
  Example (a04 func_8010FF6C, 2 off: retail's hoisted `lui s4` comes before `li s6,1`): the literal 1 in the
  loop needs T>=30 (s*l 9 against 265 insns, edge -31), so it is not hoisted and the `one = 1;` local before the
  loop stays; placing `one = 1;` inside the loop (top, after the counter store, in the while condition) gives 2 / 5
  / 18: the order of moved insns follows their order in the loop.
- install_c: a prototype the target has for a function used as a value (`void f(void);`) is rewritten to the
  installed definition's header (conflicting types otherwise; a02 func_8010CFAC); a prototype from a definition
  further down is K&R when some call passes fewer arguments.

- Never name a tool after a stdlib module (`tools/queue.py` would shadow `queue`, which concurrent.futures imports,
  for every tool run as `python3 tools/X.py`): the work queue is tools/workqueue.py.

- install_c (round 12): a prototype taken from a definition can land above the typedef it names (parse error: move
  the typedef up; since 2026-11-26 install_c declares it K&R when the type is defined further down); a multi-line `#define` ending with `}` can still be taken for a function (end it with
  `} /* end */`); alias renaming skips macro bodies (use the alias name inside a macro); callee prototypes with a
  narrow return type (`s16 f()`) change every caller in the file (keep s32, narrow at the use).
- sibling.py needs a program list (none = nothing searched); variants.py `--set` needs `\|` / `\&` inside single
  quotes, `--alts` blocks may fail without leading indentation. Never `pkill -f` a background tool (blocked): TaskStop
  or let it time out.

- Round 13: nearcopy `--install` in the background races a parallel install_c (half-edited files); install_c drops a
  scratch `extern` when the target declares the symbol later with another type, then fails "undeclared" (use the
  target's alias names); permlines misses functions returning a pointer; sibling.py misses ports that differ in
  callee names; nearcopy `--near` counts an alias name of the same address as a difference; regswap's narrowing split
  can rank a pointer truncation best (ignore it).

- Round 15: a scratch data extern with another type than the program's declaration passes ccheck and fails
  install_c (use an alias name); an earlier prototype with another return type gives "conflicting types"; a void
  definition whose caller does `return f(x);` needs a cast at the caller; a full scratch prototype breaks m2c's
  zero-argument callers (K&R); regswap `fork` can produce a variant whose uses are not dominated by the fork (check
  it); install_c needs one-line macros. Never `rm -rf build/permute` or other shared build dirs wholesale.

- Round 16: tools/jtbl.py paired same-shape tables that tie on their lowest label wrongly (now in table address
  order); install_c drops a static inline helper reached only through a `#define` (call it directly) and reads a
  macro whose body starts with `if (...) {` as a function; ccheck reports DIFF for a scratch calling a static inline
  defined only in the target file (install_c is fine); `ccheck | tail && install_c` installs even on failure;
  `git add X; git commit -- ... $(git ls-files -m ...)` leaves a staged alias file behind (name it explicitly);
  never `rm -rf build/tmp_regswap_*` while other agents run.

- Round 17: install_c inserts a scratch's narrow prototypes (`s32 f(s16)`) above later functions of the target, whose
  calls then change; the link DIFF shows up far away (a jump table or data pointer). Drop narrow prototypes from
  scratches (K&R or none); `extern void f(u8 *);` breaks callers that use the value; a prototype with fewer
  parameters than an existing call fails "too few arguments".

## Decisions (with dates in STATUS)

- Native port, stage 1 (2026-11-27): `port/` follows Tombi-Decomp's fixed-address `port/` (PS1 RAM at 0x80000000 in
  an i386 process, MIPS interpreter for code without C, Psy-Q shims), not its native-pointer `port2/`, because T2 is
  not fully matched yet. Build: `cmake -S port -B build/port -G Ninja && cmake --build build/port`; run
  `build/port/tomba2 --frames N --dump-frames DIR [--pad-script ...]`. It only reads src/, build/main.elf and
  asm/main/: matching work needs no change for it, and every function matched becomes native at the next port build.
  Port pitfalls (docs/PORT.md): gcc 2.8 accepted conflicting declarations (`int f();` then `u8 *f(...)`), the host
  does not (gen_t2.py renames such definitions); functions with inline asm stay interpreted; calls with fewer
  arguments than the callee reads (`f()` relying on `$a0`, `((s32 (*)())f)()`, `ApplyMatrixSV(p)`) get the caller's
  own arguments forwarded (PORT_ARG) by arity from the asm; a `void` C function whose asm callers read `$v0` relies
  on `eax` surviving.
- Native port, stage 2 (2026-11-27): arities for forwarding come from every program's asm, not only the caller's
  (MAIN C calls overlay functions by name: `func_800633B0(a)` -> A01 `func_8010ACB8` reads `$a1`); narrow native
  results are extended for MIPS callers. A port crash is bisected against the retail code: `--interp-range all`
  first (all MAIN functions interpreted), then `--interp-range LO-HI` on the upper bound with a fixed low bound
  (a native caller hides a native callee from the range), then gdb watchpoints and `--watch-pc`. `--window` runs
  T1's SDL2 viewer process (`build/port/tomba2-view`, needs `libsdl2-dev`). The overlays' C is native with
  `<ovl>_` names and dispatch on the resident overlay; a game function named as a value compiles to its retail
  address. Check any port change by frame diffs against `--no-ovl-native` (pixel-identical expected), and when
  they differ bisect with `--ovl-interp NAME`, `--interp-range` and `--interp ADDR` (only calls from interpreted
  code, thunks and pointers are redirected: test a native caller and its callee together). Matched overlay C
  becomes native at the next port build. Generator rules learnt in stage 2: arities by address for an overlay's
  own names of MAIN functions; `p->fn()` with an empty argument list gets the caller's arguments; block-scope
  prototypes are not calls; a dropped static helper drops its callers; GTE inline asm is translated
  (`translate_asm`). Keep `game/usa.img`: the port reads XA audio from it (the extracted XA files have no
  subheaders). Windows (stage 3, 2026-11-28): the native exe runs; `bash tools/port_win_package.sh OUT.zip`
  builds the player's zip (tomba2.exe, tomba2-view.exe, tomba2-launcher.exe, SDL2.dll, README.txt). Test it under
  Wine: `mkdir -p /run/user/0 && chmod 700 /run/user/0` first (without an XDG runtime dir Wine 9.0 aborts with
  `free(): invalid pointer` before any program runs), `WINEPREFIX=<scratch>/wp WINEARCH=win32 WINEDEBUG=-all wine
  build/port-win/tomba2.exe ...`, and compare its frame dumps with the Linux build's (identical expected). Rules
  learnt: native code must never dereference KUSEG (0x10000-0x1FFFFF: Windows keeps its own memory there, a
  committed block is read silently); the mask sources so far are main()'s primitive pointer D_800BF544
  (mips_interp.c `kcell` stores its KSEG0 view, gen_t2.py `kuseg_link_stores` keeps the 24-bit OT links) and the
  actor animation pointer at +0x38 with its bit-31 flag cleared by func_80075FF8 (gen_t2.py `kuseg_field38`,
  `port_kptr`). A new one shows as a site in `build/port/tomba2 --no-kuseg` (the tally at exit) or as a Wine frame
  differing from Linux; `port_low_emulate` also covers `mov moffs` (page-0 constants such as `*(u8 **)0x110`). The
  exe reads the disc image itself (`--disc .bin/.img/.cue/.iso`, MAIN.EXE by SHA-1) and embeds no game bytes (the
  overlay funcmap holds hashes of the first code bytes, not the words).
- Byte-matching only; tools/nonmatching.py is kept unused.
- USA is the reference; EU in config/eu/.
- The licensed-region module at the end of boot.c [0x80011A0C, 0x80012D2C) is library-style files in
  src/boot/psyq/region/ (built with the library compiler; not a known Psy-Q library).
- The loop-hoisting compiler patch (2026-11-23) will be per-file set-ups like nocse, never a replacement.
- gcc-2.8.1-nocse is a set-up of the library (made reproducibly by tools/setup_native.sh).
- decomp.dev no longer accepts new projects (checked 2026-11-22).
- Tomba2Edit is a source of names and meanings only (no license, its Ghidra C export not shipped): release 0.5.0
  (2026-11-24) added globals and NPC field meanings (docs/TOMBA2EDIT.md, `T2E` comments in include/actor.h), no
  function names and nothing that matches. Re-check new releases for `decomp/` changes; `import_names.py` takes
  only function starts.

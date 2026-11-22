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
     tools/setup_native.sh makes it from the stock cc1 (one byte patched, sha1 checked).
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
  marked "asm by design" (tools/asm_by_design.py) and count as done.

## Order of work for a scope

1. **Families**: `python3 -I tools/families.py --by-scope`: pending functions with exact copies in several programs.
   Match one, then `python3 -I tools/nearcopy.py <progs> --install` fills the copies.
2. **Inlined bodies**: `python3 -I tools/inlined.py <progs>` (build/inlined_<progs>.csv): pending functions that
   contain a matched function inlined. Copy the matched C as a `static inline` helper (`/* NAME, inlined */`) and
   call it. Big dispatchers are usually a switch over several such handlers: `python3 -I tools/dispatch.py --list
   <progs>`, then `tools/dispatch.py PROG NAME` writes the scratch (helpers + m2c caller skeleton with the helper
   calls in place; read its notes on shared tails), fix types and the cases, ccheck, install.
3. **Near misses** listed in STATUS (1-12 words off), with the tools below.
4. **Medium and large functions** (0x200+ bytes): the small ones are mostly done; bytes are what is left.
5. After each batch: nearcopy over your programs (copies of your new C); list copies in other scopes for the
   coordinator.

## The loop for one function

- Draft: `python3 -I tools/decomp.py NAME` (m2c, jump tables included). m2c invents constant arguments for calls
  whose register is not set on that path (decomp.py flags them after the draft: `/* decomp.py: F at ADDR: a2 not
  written on every path ... */`), and leaves "uninitialised" locals that are really incoming parameters.
- Check: `python3 -I tools/ccheck.py FILE.c --prog P --func NAME [-v] [--sbs] [--no-protos]`. `--sbs` is the
  side-by-side diff (read it, do not guess from word counts). ccheck masks relocations: only the linked build proves
  two globals are not swapped. `--no-protos` compiles as install_c will (it drops scratch prototypes).
- Search: `tools/variants.py` (several `//--` variants, `--set`, `--alts K=FILE`), `tools/permlines.py` (lines marked
  `//P`; `--exhaustive` for up to 7 lines; check that a result does not use a variable before it is set),
  `tools/regswap.py` (register-choice rewrites: declaration order, `do { } while (0)` wraps, parameter copies,
  loads before stores, early constants, cast <-> `MEMBER_AT` member, volatile, duplicated tails, ternaries, per-path
  locals), `tools/prio.py --prog P` (pseudo priorities and registers from the cc1 dumps next to retail's register;
  `--sched` the scheduler priorities when ccheck says `order only`), `tools/hillclimb.py`, `tools/permute.py`
  (decomp-permuter),
  `tools/magicdiv.py` (divisor of a magic-number division). Hand work from a draft beats hillclimb (about 5 minutes
  per function against hours of search); give up on a function after about 10 minutes without progress.
- Install: `python3 -I tools/install_c.py FILE.c --prog P` (game C) or `tools/install_lib.py FILE.c --prog P`
  (library files). Both check the linked build, lock per program, merge alias lines, take K&R definitions and static
  helpers, and end with `NOT INSTALLED: ...` on failure: read the last line. Write scratch C without prototypes and
  cast arguments that need s16 conversions.

## Parallel rounds (coordinator and agents)

- One coordinator, five hand-matching agents on disjoint scopes (main game code; the library; a00-a03; a04-a08;
  a09-a0l + game/demo/opn/sop/crd + boot game code), then one tools agent alone (it implements the tool ideas of the
  round; nobody else edits tools/ meanwhile).
- Agents: touch only the scope's files; never edit tools/, never run dupsweep, never `tools/build.py` without
  `--no-split`, never `rm -rf build asm`; `-j 1` (4 CPUs for 5 agents); commit every few functions with a pathspec
  (`git add F && git commit -m MSG -- F`, include the config/aliases_<prog>.ld the C needs, in the same commit);
  never push; scratch only in the session scratchpad. Final report in English: functions per program, copies in
  other scopes, near misses (words off, scratch path), recipes, tool ideas.
- Coordinator at the end of a round: clean full build (`rm -rf build asm && python3 tools/build.py`, 29 OK; commit
  the sync_src normalisation), `tools/nearcopy.py --install` and `tools/dupsweep.py --install` over all programs,
  full build again, STATUS section + this file + CLAUDE.md, `tools/readme_progress.py`, pull, push to master and the
  session branch.

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

**GTE**
- `gte_ldfcdir(0,0,0)` for the "handwritten" functions starting `addu t0,zero,zero; ... ctc2 t0..t2,$21..$23`;
  offset macros `gte_ldv3c` / `gte_stsxy3_g3`; DQA/DQB loads with custom asm (`ctc2 %0,$27`); draw loops with
  private macros (command word without nops, packed vertex loads, one `swc2` per SZ) and scratchpad pointers as
  locals (`s32 *flg = (s32 *)0x1F800000`).

## Tool pitfalls (open ones are listed in STATUS)

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
- install_c: a prototype the target has for a function used as a value (`void f(void);`) is rewritten to the
  installed definition's header (conflicting types otherwise; a02 func_8010CFAC); a prototype from a definition
  further down is K&R when some call passes fewer arguments.

## Decisions (with dates in STATUS)

- Byte-matching only; tools/nonmatching.py is kept unused.
- USA is the reference; EU in config/eu/.
- The licensed-region module at the end of boot.c [0x80011A0C, 0x80012D2C) is library-style files in
  src/boot/psyq/region/ (built with the library compiler; not a known Psy-Q library).
- gcc-2.8.1-nocse is a set-up of the library (made reproducibly by tools/setup_native.sh).
- decomp.dev no longer accepts new projects (checked 2026-11-22).

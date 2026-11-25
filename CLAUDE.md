# Working on 2tombi2decomp with Claude Code

Read this first in every session. The current state and the open tasks are in `docs/STATUS.md`; keep that file up to
date as work lands (it is the hand-off between sessions). **AGENTS.md** holds the distilled method: compilers and
set-ups, the order of work, the parallel-round workflow, the recipe catalogue and the decisions. **Always (the
user's standing instruction): every new piece of information — a recipe, a tool, a compiler fact, a decision, a
pitfall — goes into AGENTS.md and CLAUDE.md as well as STATUS.md, in the same commit as the work or the round's
integration.** Agents' briefs point them at AGENTS.md.

**First thing in a new cloud session:** run `bash tools/session_bootstrap.sh`, without being asked. It installs the
packages and the PS1 toolchain, downloads and extracts the discs from the `GAME_FILES_URL_T2_*` environment variables,
fetches the Psy-Q signatures and runs the matching build of every program (a few minutes plus the downloads). It skips
whatever is already there. If a variable is missing, tell the user to add it in the cloud environment's settings and
start a new session.

## The project

A matching decompilation of Tombi! 2 / Tomba! 2: The Evil Swine Return (PS1, 1999), and later a native port, built the
same way as the first game's project, `afsenovilla/Tombi-Decomp` (the reference: clone it read-only next to this repo
when its tools or notes are needed; copy and adapt, do not reinvent). Reference version: **USA SCUS-94454** (since 2026-11-13: Tomba2Edit and the Tomba Club research are on USA
addresses; EU SCES-02147 is kept as a second version in `config/eu/`).
Discs: docs/DISCS.md. Plan and numbers: docs/PLAN.md. **Step-by-step roadmap: docs/ROADMAP.md.**

## How to talk to the user

- Reply in **Spanish**, short and direct, first person. Never claim something works without verifying it; say
  plainly what was tested and what was not.
- **Everything generated is in English**: docs, reports, agents' reports, notes, commit messages, and the labels,
  titles and captions inside generated images. Only the chat replies are in Spanish.
- Show the user what was found at each step; ask before big decisions (repo layout, reference version, tooling that
  is hard to undo).

## Hard rules

- **Never commit** game/SDK binaries, disc images, extracted assets, game graphics, text dumps, screenshots or saves.
  "Ship scripts, not pixels": everything is rebuilt from the user's disc at build/run time; tables hold addresses,
  offsets and names only. Game URLs live only in secrets / environment variables (`GAME_FILES_URL_T2_EU`,
  `GAME_FILES_URL_T2_ES`, `GAME_FILES_URL_T2_USA`). `game/`, `asm/`, `build/`, `include/psyq/` are git-ignored.
- Never modify `.claude/settings.json`.
- Git: commit explicit paths only (no `git add -A`), no amend, no force push, `git pull --no-rebase origin master`
  before pushing to `master`. Never `pkill -f`. Every commit ends with the trailers the session gives
  (Co-Authored-By / Claude-Session). No model names anywhere in the repo.
- The user does not review PRs: verified work (the matching build still OK) goes straight to master. Open a PR only
  when asked.
- Disk in the cloud container is small: delete builds/dumps when done (`rm -rf build asm` is always safe: the build
  regenerates them); agents in worktrees must clean up. Only the USA disc image is kept (`game/usa.img`).

## How the work is run (since 2026-11-22)

- The user asked not to be asked: take the decision, say what was decided and why, and go on. Agents run on the most capable model with
  high effort, five at a time.
- Cycle: five hand-matching agents on disjoint scopes. Since round 8 (2026-11-23, the user's choice): main; a00-a01;
  a02-a03; a04-a08; a09-a0l + game/demo/opn/sop/crd + boot game code. The library has no fixed agent any more (it
  yielded ~4 KB a round against 14-17 KB for an area agent; 4 % of the bytes left): it is worked in the tools passes
  when a new compiler set-up or recipe unblocks it, or in an occasional round -> the coordinator integrates (clean full build 29 OK, nearcopy + dupsweep over all programs,
  STATUS / AGENTS.md / CLAUDE.md / README, push) -> one tools agent implements the round's tool ideas alone -> next
  round. The agents' rules and the coordinator's checklist are in AGENTS.md ("Parallel rounds").
- The coordinator's end-of-round checklist is one command since 2026-11-23: `python3 -I tools/integrate.py --since
  <previous integration commit>` (clean full build twice with the sync_src report, nearcopy + dupsweep, full build,
  README / phases, and which commits of the round do not link, built in a temporary worktree). It never commits or
  pushes. Agents take their targets from `python3 -I tools/workqueue.py <their progs>` (bottom-up queue).
- Never push a round before the clean full build: agents' intermediate commits have broken the link more than once
  (an alias line committed later, a shared aliases file rewritten).
- Compiler facts that matter: game code is gcc 2.8.1 + ASPSX 2.79 (`-O2 -G0 -funsigned-char`); the library needs the
  set-ups in AGENTS.md ("Compilers"): gcc 2.8.1 `-mno-split-addresses` or gcc 2.7.2 with GNU as, `// EPILOGUE sony`,
  `// RETURN sony`, and `gcc-2.8.1-nocse` (Sony's library compiler had no post-reload CSE; made by
  tools/setup_native.sh from the stock cc1, one byte, sha1 checked).
  The library compiler also hoists more loop invariants around loops with calls (a `loop_has_call` patch of cc1
  reproduces it per file: `// CC gcc-2.7.2-loop4`, `gcc-2.8.1-loop2`, `gcc-2.8.1-nocse-loop2`, made and sha1
  checked by tools/setup_native.sh; AGENTS.md "Compilers" item 5).
- What is left (2026-11-25, 4847 / 7011 functions, 47.1 % of the bytes): mostly actor state machines (the NPC ones of
  one skeleton are nearly done: `tools/npcsm.py --list`; AGENTS.md "Round 10 / 11 forms") and dispatchers built from matched handlers (AGENTS.md
  "Order of work" item 3), the big areas a00-a08 above all.
- Agents' commits do not always link on their own (alias lines committed later): verify with a clean full build
  before every push; time-box agents (about 70 minutes) when the user gives a time budget.
- The cloud container can restart mid-round (twice on 2026-11-24): the disk survives, running agents do not. After a
  restart: check `git log`, run `tools/integrate.py --only-since <last pushed>` (link check of each commit), push the
  newest commit whose clean full build is 29 / 29 (a temporary worktree build), and relaunch the round's agents with
  a note of what is already committed (their scratch files are still in the scratchpad).
- Library C is adapted from psx_tomba, psyz (/opt/psyz) and psy-q-decomp (/opt/psy-q-decomp), all MIT: say so in the
  file and in THIRD_PARTY_NOTICES.md.

## Build cheatsheet

- `python3 tools/build.py [prog ...] [--no-split]`: splat + assemble + link of each `config/<prog>.yaml`, sha1 compared
  with the retail file (USA; `--version eu` for config/eu). Programs: `boot` (SCUS_944.54), `main` (MAIN.EXE), the overlays `a00`..`a0l`, `crd`, `demo`,
  `game`, `opn`, `sop` (BIN/*.BIN).
- `python3 -I tools/funcstats.py --csv build/funcs.csv`: function census (Psy-Q 4.4 library by signature, code shared
  between programs, game code left).
- `python3 -I tools/progress.py [--phases]`: game / library functions in C per program, or per roadmap phase;
  `python3 -I tools/readme_progress.py` rewrites the progress block of README.md.
- Library: `python3 -I tools/libsweep.py [--prog boot] [--epilogue] [--nocse | --only-nocse] [--names A,B] --install`
  (automatic candidates; `--epilogue` adds the `// EPILOGUE sony` / `// RETURN sony` set-ups, `--nocse` the
  gcc-2.8.1-nocse ones), `tools/libnear.py [--epilogue] [--nocse]`, `tools/libpermute.py`,
  `tools/asm_by_design.py` (`--game [--write]`: game functions hand-written in assembly, a `// ASM by design:` line
  above their INCLUDE_ASM; 12 GTE list builders marked 2026-11-24); one file per library function in `src/<prog>/psyq/<lib>/`. Hand-written library C:
  `python3 -I tools/install_lib.py FILE.c [--prog boot] [--auto] [--dry]` (each function into its own file with the
  scratch's set-up header, or the first libsweep set-up that matches with --auto; build-checked).
- Set-up lines of a C file (tools/cc.py): `// CC`, `// FLAGS`, `// ASPSX`, `// AS gnu`, `// EPILOGUE sony` (Sony's
  library epilogue), `// RETURN sony` (one shared `jr ra; nop`, tools/sonyret.py; `sony first` also keeps an early
  `return K;` after its test, `sony thread` sends a branch to a `j ret; li v0,K` block straight to the return);
  `// CC gcc-2.8.1-nocse`: the library compiler without post-reload CSE; `// CC gcc-2.7.2-loop4` /
  `gcc-2.8.1-loop2` / `gcc-2.8.1-nocse-loop2`: it hoisting more loop invariants around calls (setup_native.sh,
  libsweep / libnear `--loop`, pzsweep `--loop` / `--cc A,B`); ccheck.py and variants.py take
  `--cc --flags --as --aspsx --epilogue --return` overrides.
- C lives in `src/<prog>/*.c` (`INCLUDE_ASM` for what is not decompiled yet, `include/common.h`); see docs/STATUS.md.
- `python3 -I tools/decomp.py NAME [--check] [--write]`: m2c draft of one function; `python3 -I tools/sweep.py
  [--max-size 0x100] --install`: install every draft that matches as is (build-checked).
- Hand-written C: check a scratch file with `tools/ccheck.py FILE.c`, install with `python3 -I tools/install_c.py FILE.c
  [--prog main]` (build-checked; on a failed build it prints the compiler's first error lines; callers with another
  argument count become `((RET (*)())f)(...)`; a clashing scratch macro is renamed; it says when to commit
  config/aliases_<prog>.ld too); recurring fixes are listed in docs/STATUS.md.
- `python3 -I tools/permute.py NAME --src FILE.c`: decomp-permuter with the game's pipeline (near-misses).
- `python3 -I tools/sibling.py [PROG ...] [--ratio 0.65] [--install]` / `tools/sibling.py --from PROG:NAME [--src
  FILE.c] [PROGS]`: the family template method as a tool (2026-11-24 (9)): matched C (or one function, also from a
  scratch not installed yet) put into pending siblings of other lengths too, then edited in rounds from the asm
  alignment: immediates (relocated words excluded), lh / lhu and lb / lbu sign flips of the access at that offset,
  stores retail has (`store+`, or `store=` another value) or does not have (`store-`), adjacent statements swapped
  (a store before / after a call) when within 12 words; build/sibling/<prog>/[near/]<name>.c with the edits made.
  After matching one member of a family: `sibling.py --from PROG:NAME --src scratch.c` for the others.
- `python3 -I tools/nearcopy.py [PROG ...] [--install] [--ratio 0.8 --near]`: matched C from any program put into
  near copies (patched constants / offsets, renamed symbols); `--near` writes the closest C of the rest to
  build/nearcopy/<prog>/near/ for hand work (a `// retail diff:` line: constants only / extra or missing block at
  +off / registers / callees). `tools/dupsweep.py`: exact copies only.
- ccheck (2026-11-24 (9)) compares every jump table the function addresses with retail's jtbl (a wrong case-to-label
  mapping is `DIFF ..., code equal, jump table differs` with the entries, not an OK that fails the link) and warns
  on scratch declarations of a function the program or main defines with another return type or as data
  (`extern u8 f[];`).
- `python3 -I tools/ccheck.py FILE.c --prog P --func F --sbs` (or `tools/sbs.py FILE.c F --prog P`): side-by-side
  diff, ours vs retail. `tools/permlines.py FILE.c F --prog P`: moves the lines marked `//P` until it matches.
  `tools/variants.py FILE.c F --prog P [--set 'k=a|b'] [--alts K=ALTS.txt]`: words off of each `//--` variant in the
  file (`--alts`: `{K}` takes each `@@`-separated block of ALTS.txt). `tools/ccheck.py --no-protos`: compiles a
  scratch with its prototypes dropped as install_c.py does. GTE code: `#include "gte.h"` (real command words).
- `python3 -I tools/families.py [--top 40] [--by-scope]`: pending functions of all programs grouped by opcode
  sequence, copies x size (build/families.csv; `--by-scope` per agent scope, mixed families apart): the hand-work
  targets where one match gives several.
- `python3 -I tools/inlined.py [PROG ...] [--from P,...] [--min-cover 0.8]`: pending functions that contain an
  inlined copy of matched C (registers renamed, prologue / epilogue dropped; build/inlined.csv for all programs,
  build/inlined_<progs>.csv for a scope; `{op:K->K2}`: constants that differ in the copy; `--repeats`: one block
  several times in a pending function, build/repeats*.csv): copy the matched C as a
  `static inline` helper headed `/* NAME, inlined */` and call it (install_c.py dedupes / renames helpers).
- `python3 -I tools/workqueue.py [PROG ...] [--top 30] [--max-size N]`: bottom-up work queue (build/queue_<progs>.csv):
  pending functions with their callees (pending count, MAIN / boot resolved), jump tables, inlined bodies
  (inlined.py csv), family / exact copies, callers; no pending callee first, then size x copies. (Not tools/queue.py:
  that name shadows the stdlib module concurrent.futures imports.)
- `python3 -I tools/integrate.py [--since REF] [--only-since REF] [--skip-clean] [--skip-sweeps]`: the coordinator's
  end-of-round checklist (AGENTS.md "Parallel rounds"); never commits.
- include/actor.h: `typedef struct Actor` (the common actor fields by offset, types from a census of the matched C);
  `tools/decomp.py NAME --actor [--actor-args 0,1]` (also statemachine.py / dispatch.py `--actor`) drafts with arg0
  as `Actor *`: far fewer casts, same scores; matched C is not rewritten to use it.
- `python3 -I tools/npcsm.py --list [PROGS] [--all]` / `tools/npcsm.py PROG NAME|ALL [--install]`: the NPC actor
  state machines (func_8007A624 + an init call, `switch (a[4])` skeleton; 139 pending 2026-11-24): drafts in
  build/npcsm/<prog>/ restructured into the skeleton, ccheck'd, permlines over the case-0 stores of near drafts
  (`--perm-max 40 --perm-seconds 60`, `--no-perm`). A start for hand work (1 of 139 matched as drafted).
- ccheck warns when the scratch compiles differently with its prototypes dropped (install_c's form;
  `--skip-protos-check`); `--sbs --real` / `tools/sbs.py --real` hide relocation-only differences. install_c makes
  narrow-parameter prototypes of callees called elsewhere K&R and prints the first differing `FUNC+0xOFF` on a link
  DIFF. regswap: `--hacks` for the const kind; kinds emptycase / caseinc / vstore / perarm. permlines: nothing moves
  past break / return. integrate.py removes build/tmp_regswap_* older than 2 hours; workqueue csv has size_hex.
- `python3 -I tools/statemachine.py --list [PROGS]` / `tools/statemachine.py PROG NAME`: actor state machines (rodata
  jump tables): build/statemachine/<prog>/<name>.c with every table's cases (operand, target, calls, inlined matched
  bodies), the helpers and the closer of the dispatch.py / decomp.py drafts; write each case in full, drop the header.
- `python3 -I tools/dispatch.py --list [PROGS]` / `tools/dispatch.py PROG NAME`: a pending function holding several
  matched bodies (inlined.py) -> build/dispatch/<prog>/<name>.c, the bodies as `static inline` helpers + an m2c
  caller skeleton with each inlined span replaced by the helper call (read its header notes: shared tails), ccheck'd.
- `python3 -I tools/regswap.py FILE.c F --prog P [--skip K,...]`: greedy register-choice rewrites of a near miss
  (declaration orders, store through a temporary, reuse / fork / copy / per-path split of locals, `do { } while (0)`
  wraps, parameter copies, loads before the previous store, constants as early locals, cast <-> `MEMBER_AT`
  struct member, volatile re-reads, goto -> duplicated tail, ternary <-> if / else, a call result through a dead
  local, abs variants; `--max-seconds S`; narrowing splits only with `--narrowing`).
  New kinds (2026-11-24 (4)): `copy` / `keep` (a copy in its own register, only where it dominates the uses),
  `callcopy`, `barrier` (`__asm__ volatile("");`), `swapif`, `perbranch`, `ptrlocal`; ccheck prints `score N`
  (regswap's aligned count) for another length and warns on calls with another argument count than the target's
  definition. `python3 -I tools/loophoist.py FILE.c F --prog P`: gcc's loop movables (cc1 -dL; moved or not, the
  value) and the constants loaded before vs inside each loop, ours and retail. `tools/statemachine.py PROG NAME
  --cases`: the retail asm per case block (exits, calls) in build/statemachine/<prog>/<name>.cases.txt.
  `python3 -I tools/prio.py FILE.c [F] --prog P [--sched]`: gcc 2.8's pseudo priorities and hard registers from the
  cc1 dumps next to retail's register for each (what priority a pseudo would need); `--sched` the scheduler
  priorities per insn (ccheck says `order only` when only the order differs).
- `python3 -I tools/pzsweep.py [--prog main,boot] [--install]`: psyz / psy-q-decomp files compiled whole under the
  library set-ups, every function compared with every pending library function of the same size (any name).
  `tools/permlines.py ... --exhaustive`: every order of at most 7 marked lines (`//P` lines stay in their block
  and case; `--max-seconds S`). `tools/nearcopy.py --lib`: library
  files between main and boot.
  `tools/magicdiv.py MULT --shift S [--unsigned]`: the divisor behind a magic-number multiply.
- install_c.py renames symbols named after another program's addresses from the relocations (C copied between
  overlays installs as is); libsweep.py maps foreign library names with `#define` and tries the extra set-ups.
- `python3 -I tools/ccheck.py src/main/<file>.c`: compile with the game's compiler (gcc 2.8.1 + ASPSX 2.79,
  docs/COMPILER.md) and compare every function in the file with the retail bytes.
- `python3 -I tools/t1sweep.py [--t1 ../afsenovilla/tombi-decomp] [--matched] [--reuse] [--ratio 0.8]`: Tombi! 1's
  game C (Tombi-Decomp, MIT) compiled with this pipeline and compared with every pending function (build/t1sweep.csv).
  Run 2026-11-23: nothing within 4 words, no ratio >= 0.8; what T2 shares with T1 is already matched. Not worth more
  effort (STATUS "2026-11-23 (4)").
- `python3 -I tools/import_names.py /opt/tomba2edit --write [--eu]`: names from Tomba2Edit (docs/TOMBA2EDIT.md).
  Release 0.5.0 (2026-11-24): no new names, no C export; globals and NPC field meanings in docs/TOMBA2EDIT.md and
  include/actor.h (`T2E` comments).
- Round 12 (2026-11-25): sibling.py needs a program list (none = nothing searched); Round 12 forms and install_c
  pitfalls in AGENTS.md.
- `python3 -I tools/vermatch.py`: how much USA code is found in the EU / ES builds.
- `python3 -I tools/gen_configs.py game/usa [--force] [--out config/eu]`: regenerates the first configs (keeps hand-made ones without --force).

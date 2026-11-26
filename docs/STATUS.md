# Status and open tasks (hand-off between Claude Code sessions)

Update this file whenever something lands or a task is decided. Newest first.
The step-by-step plan is docs/ROADMAP.md (tick its boxes as steps land).

## 2026-11-27: fifteenth round

All code in C: **5104 / 7011 functions (72.8 %, 54.1 % of the bytes)**, from 5015 (52.0 %). main +29 (~11.7 KB, Tomba
state handlers ~2 minutes each), a04-a08 +23 (~13.9 KB), a00-a01 +15 (~12.8 KB: the last two big barrels, a01 +11),
a02-a03 +10 (~9.3 KB: the two trolley physics functions), a09 scope +10 (~8.9 KB). The coordinator installed a02
func_80111974 after declaring its raw-word jump table (jtbl_801092FC in config/symbol_addrs_a02.txt); nearcopy put a01
func_8010CF68 / func_8011D9E4 into a04 func_8010BE1C / func_80129744. integrate.py: clean build 29 / 29; a7a5ea4 (a02
func_8010B634) does not link alone. Recipes in AGENTS.md "Round 15 forms".

Near misses (scratch in r15b/<scope>/): a03 f_UpdateStandardTrolleyPhysics 3 (sibling of the matched Upgraded one),
main func_80053E50 3, a0a func_801179C0 4 and its twin a0e func_80116D48 4 (the 0x500 skeleton has 4 more members,
a0b func_80116520, a0c func_80116A38, a0d func_801162F4, a0f func_80119CC0: ~7.8 KB behind one `lhu 0x62` placement),
a06 func_80123948 4, a00 f_UpdateTownBarrelChildTransforms 4, a01 func_8010EFBC 4, a0b func_80116B50 5, a05
func_80114874 6, main f_SpawnScriptedPresentationActor 6, a01 func_801208B4 6, main func_80036240 7, a04 func_8013D0F8
15, a01 func_80132FD0 16, a05 f_SpawnKujaraSummitSceneActorsFromPlacementTable 17 (shared-lui spawner pattern, 5
functions ~5 KB), a06 func_8011D520 18, a01 func_8012702C 20, a02 func_80118C54 22, a00
f_UpdateBarrelSeesawSupportHeight 22, a07 func_8012DBB4 23, main func_80025B78 24, func_8003E030 58, a0b func_80109F7C
52 (collision family), a02 func_80115F58 ~66, main func_800696C4 ~68, a06 func_80125338 ~260. Open: a00
f_InitializeTownBarrelSeesawController (0x710), a0d f_UpdateEarthEvilPigSplitActor (0xF0C), a0g
f_UpdateCourageTowerInteriorEntranceActor (0x6D0); a02 func_8010CF30 is a split-off tail of func_8010C8E4 (config
merge needed). Possibly ASM by design: a0a func_8010FD74, a0d func_801131B0 (handwritten mtc2 in normal frames).

Tool work left: jtbl.py accepting raw-word dlabel tables whose entries fall inside the function and never picking a
table whose labels lie in another function; a census of prologue-less fragments that read saved registers; a
"reverse inlined" list (pending functions equal to a case body or static inline helper of matched C); a
strength-reduction (giv) report from the cc1 loop dump; a sched1 dependency probe (which stores each load depends
on); install_c: cast callers of a void definition, K&R when a scratch prototype clashes with zero-argument calls;
ccheck: data extern type clashes, prototype return-type clashes, hints for uninitialised locals and lh / lhu of one
field; regswap: expression per arm, invariant pointer-local placement in loops, copy into a second variable, fork
dominance check, `-j 1` default; variants: auto-escape `|` in `--set`; tools write PID files (pkill -f is denied).

## 2026-11-26 (3): fourteenth round

All code in C: **5015 / 7011 functions (71.5 %, 52.0 % of the bytes)**, from 4926 (49.3 %). Same method as round 13.
a09 scope +32 (~37 KB: a0a's 0xD04 evil-pig hit / capture state machine and its 5 copies, the evil-pig attack / intro
skeleton across a0a..a0f, a0k), a04-a08 +16 (~15.5 KB: the a08 Tomba water code and its floor probe func_8012DE84,
which blocked 16; Tomba state handlers), main +15 (~9 KB), a00 +12 (~5.8 KB: barrel / drying-rack chain), a02-a03 +7
(~5 KB; a03 +3) plus 7 streamed-audio range table copies the a02 agent generated for a00..a08 (installed by the
coordinator, a68378b). integrate.py: clean build 29 / 29; 564aca5 and bdda905 do not link alone (alias lines in the
next commit). Recipes in AGENTS.md "Round 14 forms".

Near misses (scratch in r14b/<scope>/): a0a func_801140D0 1 short (4 members; `li 2280` twice), a0k func_801147D0 1
short, a05 func_80110380 1 (or operand order), main func_800783DC 3, func_8001D940 ~3, a00 func_8011E7CC 3, a05
func_8010F0F8 4, a06 func_80112C60 4, a00 func_8013E424 5 (family a06 func_8013F320), f_SelectFeedChicksNpcSpawn 5,
main func_8002C920 6, f_UpdateActorScaledPartTransforms ~6, a02 func_80125C5C 6, a04 func_80112B50 8, a08
func_80110AA0 ~9, a01 func_8011D9E4 10 (family a04 func_80129744), main f_PrepareTombaCollisionFrame 13, a02
func_801152A8 14, func_8010D6B4 16 (one register; same block in pending func_8010D288), a08 func_8010C90C 16, main
func_8003E264 20, a00 func_80130524 21, func_80130AC4 24 (merged tails), f_UpdateBarrelSeesawSupportHeight 26, main
func_8003E030 35, a00 f_ResolveActorOnNetBridge 41, a0f func_80109ED8 74 (twin a06 func_8010E908); a08 func_8010E4CC
only its jump table hoisted. Next targets: a00 f_UpdateBarrelSeesawRide (0x7D4), f_RotateSelectedTownBarrel (0x79C);
a0d f_UpdateEarthEvilPigSplitActor (0xF0C), a0g f_UpdateCourageTowerInteriorEntranceActor (0x6D0). Possibly not ASM
by design (splat "Handwritten function" with normal frames): a00 func_8013DD34, func_8013E08C, a01 func_80132690.

Tool work left: a table-switch family generator (cases that load constants and jump to a common tail, any case
count: the round's gen_audio.py prototype in the scratchpad r14b/a02/) and a sibling.py skeleton-port mode (same case
structure, tables / constants / callees substituted); nearcopy `--near` trying to delete / add each if-block on an
"extra block" diff; sbs: unified diff of normalised asm with `--swap s0,s1`, hints for per-arm `lui; addiu`
(cross-jumped duplication) and commutative `addu` with a parameter base (typed struct), `--real` hiding constants
splat annotates as symbols; regswap kinds: per-case / per-block split of a variable, early global load into a local,
copy before test, hoist trailing statements out of an if, initial `v = K` into the else arm, per-global volatile
toggle, one pointer local per use of a global; regswap `-j` default 1; install_c casts the caller of a void
definition; ccheck warns on a pointer local to a global assigned twice and on a dropped dead store to a stack slot; a
duplicate-constant hint (retail loads `li K` twice); workqueue ranks callers of functions matched this session;
loophoist: which movables flip with N more insns; a cross-jump probe.

## 2026-11-26 (2): thirteenth round

All code in C: **4926 / 7011 functions (70.3 %, 49.3 % of the bytes)**, from 4847 (47.1 %). The brief changed after
the tools pass closed no near miss: new functions written straight from the retail asm, near misses only with one
obvious idea left. a04-a08 +22 (~26 KB: 13 by hand, 9 copies; a08 +6 after nothing in round 12), a00-a01 +21 (~20 KB:
the 12 town-creature states and their 16-case dispatcher f_UpdateTownCreatureBehaviorState 0xF28), main +18 (~6.3 KB),
a09 scope +9 (~7.4 KB), a02 +6 (~5.1 KB). integrate.py: clean build 29 / 29, all 68 commits link, nearcopy put a06
func_80112838 into a00 func_8010A7F8 / a0e func_8010AB24 and a0a func_8010B0FC into a01 func_8010A0F0. Recipes in
AGENTS.md "Round 13 forms", pitfalls in "Tool pitfalls".

Near misses (scratch in r13b/<scope>/): a05 func_80110380 1 (or operand order), a0a func_801140D0 1 short (4
members; 0x8E8 loaded twice), a0k func_8010BEF8 1 short (family a02 func_8010B068, a07 func_8010D84C), main
func_8003EA88 2, a0c func_8011353C 2, a04 func_801129C0 4, main f_SelectAreaPlaneVerticalProfile 4, a02 func_80125C5C 5,
a00 f_UpdateTownCreatureSpawner ~5, a02 func_8010DBE4 6 (scratch has a barrier), main func_80035338 6,
f_DrawFullscreenOverlay 6, func_800368D0 12 (blocks 6), a00 f_UpdateTownCreatureInteractionLifecycle ~14, a01
func_8010C498 16, main func_8006042C 21 (store-flag xori), a06 func_80129218 56 (blocks its copy func_8012945C), a08
func_80116D3C ~100 (one cause: constant 1 in a0), a06 func_80125338 190 (registers only). Pending Tomba state
handlers: a04 func_80112B50, func_801149B8, func_801150C4; a08 func_801100F4, func_80110AA0, func_801114B8. ASM by
design candidates: a0l f_DispatchEndingAreaCameraSequence (+ a00 f_UpdateWindmillCollapseParticleActor, a07
f_UpdateCircusLockerNpcActor), a0l func_80112DEC (+ a00 func_801465EC, a07 func_801311D0); splat "Handwritten
function": a00 func_8013CDD4, a01 func_80133F38.

Tool work left: variants.py `--toggle` (all combinations of N on/off edits) and a file of literal (old, new)
replacement sets; regswap kinds: `__builtin_abs`, narrow copy (`u16 b = x`), swapped operands of a repeated test,
split a term into a temporary, first-store struct-member toggle, pointer walk -> index loop, scc defeater
(`k = c ? 1 : 0` kept as branches); regswap never ranks a narrowing split of a pointer; ccheck warns on a1 / a2 set
before a jal with fewer arguments elsewhere, on store-flag conversion (`xori` / `sltu` vs branches) and on a scratch
extern clashing with the target; sbs hint for redundant zero-extensions; nearcopy / sibling: tolerate a table-choice
prologue, map callee names, plain symbol names for aliases; nearcopy --install takes a program lock; install_c hoists
the target's later declaration; permlines finds pointer-returning functions; prio.py label mapping on large functions.

## 2026-11-26: tools after round 12

One tools agent, about 90 minutes, the round-12 "Tool work left" list in its order.

- **regswap.py**: 14 new kinds (AGENTS.md "Tool pitfalls", regswap kinds since 2026-11-26): `cmpflip`, `varshift`,
  `chain`, `latestore`, `paramcopy`, `foldeduse`, `oneexpr`, `blockscope`, `twoset`, `accum`, `idxlocal`,
  `copyback`, `retshape` (the return-structure variants: goto to the final return, shared return labels, fall
  through to the final return), `intoarms` (the statement after an if / else into both arms: a cross-jump
  undone). The hack kinds (`const`, `volatile`, `vstore`, `barrier`, `varshift`, `twoset`, `idxlocal`,
  `copyback`) come after the clean ones in the `--max-cands` budget and lose ties.
- **loophoist.py**: the move_movables() arithmetic per movable and the threshold bounds of the file.
- **install_c.py**: a prototype taken from a definition whose parameter types the target defines only below the
  insertion point is declared K&R (`T f();`) instead of the full header (round-12 a0a parse error).
- Batch over the round-11 / 12 near misses (41 within 23 words; scratch census and driver in the session
  scratchpad t12/: census.py scores every scratch of r11b / r12b and keeps the best per function, batch.sh runs
  regswap over the best of each): the 14 new kinds alone (75 s each, 4 rounds, pairs on 4) closed **none**;
  a01 func_8010EFBC 8 -> 4 (`intoarms`: the statement after an if / else into both arms) and a02 func_8010FFF4
  15 -> 12 (`cmpflip` + `varshift`); the full kind set on top of those found nothing more in 300 s. The census
  also shows main func_8006DF88 at 0 only with `asm("$4")` (df88r.c; not allowed), and scores that differ from
  the agents' reports (the reports counted a variant of a `//--` file): a05 func_8013484C 4 (not 1), main
  func_8007AA38 3. All kinds (old + new, 80 s each, pairs on 4) over the 12 near misses within 4 words (main
  func_801140D0's scratch skipped: asm register): **nothing better** for any of them. These near misses are
  scheduling order (order only), loop-hoist order and one-instruction register choices that the rewrite catalogue
  does not reach; the next step there is prio.py `--sched` / loophoist arithmetic by hand, not more kinds.
- Ideas left: a scheduler-order kind driven by prio.py `--sched` (which insn needs a higher priority -> which
  statement to move or split); a loop-movable order kind (constants set inside the loop after a given insn, from
  loophoist's order of moved insns); statemachine.py jump tables through a hoisted register and unlabeled rodata;
  install_c alias renaming inside `#define` bodies; a `--kinds-new` shortcut for regswap.
- Hand tries (t12/try.py: replacements scored one at a time): a00 func_80118B10 (retail loads `a[5]` before
  `H(a, 0x62)` in case 0: early load, block-scoped temporary, store order, `(*q)++` all stay at 2 or worse),
  a0c func_8011353C (lui order of two globals: read order swapped, no volatile, pointer locals, direct operands:
  4-8, worse than the volatile form's 2), main func_8007AA38 (retail keeps `id` in v1, copies it back to a1 and
  computes `(u8)id` after the test; `s32` / `u16` / `(u8)` kinds of `kind`: 9).

## 2026-11-25: twelfth round

All code in C: **4847 / 7011 functions (69.1 %, 47.1 % of the bytes)**, from 4778 after the tools pass (45.5 %).
Agents: a00-a01 +21 (~9.5 KB: a00's town-creature callees func_801402B8 / f_UpdateTownCreatureTerrainContact unblocked
the creature states, 6 matched, ~12 left), a04-a08 +17 (~9.3 KB: contact dispatchers, four round-11 near misses),
a02-a03 +16 (~8.0 KB), a09 scope +10 (~13.9 KB: three NPC state machines and f_SelectEvilPigArenaTarget with its five
copies in a0b..a0f), main +5 (~1.5 KB, three round-11 near misses). nearcopy put a02 func_801168A0 into a07
func_80113470. integrate.py: clean build 29 / 29, sweeps nothing more; 8219523 (a02 func_8011BACC) does not link
alone (its alias line is in the next commit). sibling.py ported nothing new this round (families matched by
nearcopy or differed in shape). Recipes in AGENTS.md "Round 12 forms", pitfalls in "Tool pitfalls".

Near misses (scratch in the session scratchpad r12b/<scope>/): a05 func_8013484C 1 (delay slot from the
fall-through), main func_8007AA38 1 short, func_8006DF88 2 (matches only with an asm register), a00 func_80118B10 2,
a02 func_8010B068 2 (3 copies), a04 func_8010FF6C 2, a0c func_8011353C 2 (order only), main func_800508A8 3, a00
func_8013BCC8 3 (6 copies), a01 func_8010FD5C 3, a02 func_8010FFF4 3 short, a0a func_801179C0 4, main func_80021DF4 4,
func_8002F230 4, a02 func_80122AC4 4, func_801154DC 6, func_8011321C 6, a05 func_8013590C 6 (family of 3 with a07
func_8012D2B4, a08 func_8012A06C), main func_8007E110 8, a00 f_ResolveActiveColliderActorContacts 8,
f_UpdateLinkedTownCreatureActor 8, a01 func_8010EFBC 8, a01 f_UpdatePipeAreaScenePropActor 10, a05
f_UpdateWhosTheLiarSisterActorA 10, main func_800368D0 12 (blocks 6), a06 func_8010F450 11, func_8011D520 12, main
f_StepAngleTowardTarget 14, a02 func_801117B0 14, a08 func_8010D9AC 15 (s2 / s3), a00 func_80140544 19, a0a
func_801140D0 21 (4 copies; register pair), a07 func_8012DBB4 23, main func_8006DCF4 38. Left in a00: the
town-creature states (KnockbackBounce, HopAndBrake, ExtendedLeap, LeapingCharge, func_8014103C, FleeRun,
JumpingAttack, IdleDecision, StraightRun, ApproachTomba, VariantActivation, f_UpdateCrabBasketCarrierSequence).

Tool work left: regswap kinds (comparison orientation, variable shift, scc defeater, giv-base, chained assignment,
late store `t = x + 1 ... x = t`, parameter frame copy, swap temp reuse, folded-away use, one-expression temporary,
block-scoped pointer locals, constant through a two-set variable, store into each arm, loads into temporaries, copy
back of a parameter, accumulator -> `x0 + i*K`, literal-in-index -> locals); a return-structure variants tool
(in-place return / goto shared label / fall through) and a cross-jump defeater; loophoist: the threshold x savings x
lifetime arithmetic per movable and the distance to the edge; statemachine.py: jump tables through a hoisted
register and unlabeled rodata (a05 D_80109150); a contact-dispatch generator from the case map; install_c: types of
a definition prototype declared before its insertion point, skip pp items / rename aliases inside `#define` bodies,
data-style declarations, alias roll back / reuse; ccheck: a scratch extern clashing with the target's headers;
workqueue: a "pending callee just matched" column; decomp.py `--actor` by default for overlays; nearcopy prints
copies in other programs at the end of a scoped run; variants `--alts` without leading indentation.

## 2026-11-24 (9): tools after round 11

One tools agent, about 80 minutes, the "Tool work left" list of the round-11 entry in its order.

- **tools/sibling.py** (new): the family template method as a tool. Candidates: matched C of any program whose
  masked words align with a pending function at difflib ratio >= 0.65 (other lengths too), or `--from PROG:NAME
  [--src scratch.c]` (one function, a scratch not installed yet included, against every pending function). Each
  is compiled in the target's place and edited in rounds (beam of 3) from the alignment with retail: immediates
  (relocated words excluded: nearcopy's patches), lh / lhu and lb / lbu sign flips of the access at that offset,
  `store+` (a store of K retail has: `*(T *)(base + O) = K;` next to each C store), `store=` (another value for a
  store the C has), `store-` (a store retail does not have), and adjacent statements swapped once within 12 words
  (a store before / after a call). Matches renamed to the target's symbols (prototypes of renamed callees dropped,
  `s32 f();` when used as a value). Over all programs (64 pending functions with a candidate, about 6 minutes):
  **2 matched and installed**: a0k func_80109C0C (from a02 func_801106F0, a mask constant that turned lh into lhu;
  nearcopy refused it as not constants-only) and a04 func_80131F6C (from a04 func_8012CBD4: two stores added, one
  value changed, three constants, a store moved before a call; 15 -> 0). The rest are 12+ words off with
  differences outside the catalogue (a07 func_80110258: retail has `if (D_1F800137 == 1) D_1F800137 = 0;` in
  case 2, a conditional block; build/sibling/<prog>/near/ after a run). The population of siblings of matched C is
  small (64 at ratio 0.65): the tool pays right after an agent matches the first member of a pending family
  (`--from`).
- **ccheck.py**: every jump table the function's code addresses is compared with retail's jtbl as offsets into
  the function (`DIFF ..., code equal, jump table differs` + the differing entries; tested by swapping two case
  labels of a0l func_801092E8); scratch declarations of a function src/<prog>/<prog>.c or main.c defines with
  another return type, or as data (`extern u8 f[];`), are warned about.
- **install_c.py**: heads() skips lines inside multi-line `#define` bodies (`switch (x) { \`) and keywords.
- Not done (time box): install_c rewriting data-style declarations of the installed function, alias rollback
  after NOT INSTALLED, reuse of an existing alias (a second install of a0k made `D_1F80009C_baed_759c`), prototype
  before a helper; regswap kinds (comparison flip, variable shift, switch-value CSE breaker, scc defeater,
  giv-base), permlines inside static inline helpers, variants.py `@@` newline; sibling.py edit kinds for a
  conditional block on a global and for callee argument lists.

## 2026-11-24 (8): Tomba2Edit release 0.5.0 reviewed

Tomba2Edit 0.5.0 (commit b3fd4a6; /opt/tomba2edit updated) has no new function names (`symbols_us.json` unchanged)
and still does not ship its Ghidra C export (`decomp/MAIN.EXE_US_DECOMP.c`, read by its new `game/decomp_view.py`),
so it gives no matches. It adds meaning: a dozen globals (inventory table 0x800BFAB4, item-use flag 0x800BF80A,
current interior 0x800BF817, warp destination 0x800BF83A, file table 0x800ECF58, costume tables ...) and the NPC
skeleton's fields in words (phase a[4], script running a[5], script status a[0x70] == 255, talk box +0x80..0x86,
scale +0xB8..0xBC, yaw +0x56). Written down in docs/TOMBA2EDIT.md ("Release 0.5.0") and as `T2E` comments in
include/actor.h. Not done: renaming the `D_` globals in the C (readability only; left for the header pass).

## 2026-11-24 (7): eleventh round (NPC state machines)

All code in C: **4776 / 7011 functions (68.1 %, 45.5 % of the bytes)**, from 4626 (41.9 %). The round went after the
139 NPC actor state machines tools/npcsm.py found: a04-a08 +48 (~37 KB), a09-a0l + overlays +29 (~23 KB, the Evil Pig
battle actor family of 6 and the a0l family that was 20 words off), a00-a01 +16 (~19 KB, 14 of their 17), a02-a03 +21
(~12 KB), main +36 (~11.5 KB: actor / effect state machines ending in f_ResolveEffectEightByteStreamPayload, primitive
walkers; func_8002B278 unblocked its caller family). 29 / 29 byte-identical; an intermediate push (5ed8162) was checked
by a clean build of that commit, tools/integrate.py checked the commits after it.

Findings (folded into AGENTS.md):
- Family template method: match one member, then diff each sibling's opcode-normalised asm against it, map callees /
  symbols from the jal and %hi lists, substitute constants and store lists (six 0x4C0 functions in ~10 minutes).
- A store retail puts in a jal delay slot: `MEMBER_AT(s16, a, 0x86) = K;` (the a0l family).
- A pointer local reused in two places gets a saved register: fork it per place (fixed many NPC functions; also
  removes `lui/addiu` straight into a saved register).
- A talk-state switch repeated with different script tables: a multi-line `#define` macro (a static inline hoists the
  script address).
- Flag helpers: `if (A || B) return 1; return 0;` keeps branches; `return A || B;` gives scc.
- ccheck masks rodata: a wrong case-to-label mapping for an empty case passed ccheck and failed the link at a jtbl
  entry: read the jtbl when a switch has empty cases.
- A signed switch over a logically shifted operand: `switch ((s32)((u32)sw >> 8))`; a `srlv` by a register holding 1
  that is also the return value: `u32 k = 1; if (x >= ((u32)tbl[i] >> k)) return k;`.

Near misses (scratch in the session scratchpad r11b/<scope>/): a07 func_8010A660 1, a05 func_8013484C 1, main
func_8006BE88 2, a02 func_8010B068 2 (3 copies), a03 f_UpdateTrolleyCourseOverlayActor 2, a06 func_801229A0 2, a00
func_80127798 2, func_80118B10 2, func_8013BCC8 3 (6 copies), main func_8004F474 3, func_8002F230 4, func_80021DF4 4,
a06 func_8011159C 4, a0a func_801179C0 6 (6-member family), a01 f_UpdatePipeAreaScenePropActor 6, a02 func_801154DC 6,
main func_8006DF88 7, func_800508A8 9, func_80035640 9, a05 f_UpdateWhosTheLiarSisterActorA 10, a00 func_80132400 13,
func_80127D1C 13, main func_800368D0 19 (blocks 6 functions), a00 f_HandleKainenInteraction 20. Pending NPC state
machines left: about 20 (a00 3, a0c func_801172B0, a0d f_UpdateEarthEvilPigSplitActor 0xD80, a0g
f_UpdateCourageTowerInteriorEntranceActor, a0k func_80112884, ...: `tools/npcsm.py --list`).

Tool work left: npcsm family mode / "variant from sibling" (map constants and symbols from a matched scratch or
function to a pending sibling, ccheck'd); install_c: rewrite data-style declarations of the installed function
(`extern u8 f[];` / `extern M2C_UNK f;` -> `void f();` + casts at uses), skip `#define` bodies when looking for
functions, roll back alias lines after NOT INSTALLED, reuse an existing alias on a second install, insert a prototype
before a helper that needs it; ccheck: compare scratch prototypes with the target's definitions (return type), a
jump-table check (case-to-block mapping against retail's jtbl), expand local `#include "hdr.h"` in --no-protos, a
`--frame` hint; permlines: permute inside static inline helpers, an auto mode for loop increments; regswap: flip
comparison orientation, variable shift (`x >> K` -> `n = K; x >> n`), break CSE of a switch value reused as a
constant, an scc defeater, flip if / else for per-arm stores, "giv-base" (`q = a + K` for `a[K + i*S]`), rank clean
rewrites before hacks; variants.py `--alts` blocks need a newline before `@@`, an inline-alternatives mode.

## 2026-11-24 (6): tools after round 10

One tools agent, the "Tool work left" list of the round-10 entry below, in its order (about 60 minutes).

- **tools/npcsm.py** (new): the NPC actor state machines. `--list [PROGS]`: pending functions whose asm calls
  func_8007A624 and one of the init functions func_800519E0 / func_80051B70 / func_80040CDC, with size, whether
  the `lbu x, 4(a0)` switch is at the top (`skel`) and the transform updater it calls (func_800517F8 / 80051844 /
  800518FC). Found: **139 candidates, 0x20184 bytes**, all with the skeleton: a00 8, a01 9, a02 1, a04 15, a05 18,
  a06 14, a07 11, a08 22, a09 3, a0a 2, a0b 3, a0c 5, a0d 5, a0e 2, a0f 4, a0g 1, a0h 1, a0i 1, a0j 2, a0k 3,
  a0l 7, sop 2 (`--all`: 306 pending callers of func_8007A624). `PROG NAME|ALL`: m2c's draft rewritten into the
  skeleton (case order 0, 1, 2, 3 with `break;` ends, m2c's fall-through into the empty case 2 closed, `a[4]++`,
  m2c temporaries never assigned replaced by the case value / the head's constant, `*(void *)0x1F80xxxx` typed
  from the asm access and named `D_1F80XXXX` as retail relocates it, a global read at several offsets through a
  `u8 *g = (u8 *)&D_X;` local), each variant ccheck'd, then permlines over the case-0 stores of a draft within
  40 words. Over all 139: none matched as drafted, 3 within 10 words, 18 more within 30, 38 within 100, 29 did not
  compile (m2c types); **a0f func_801183C8 matched** after permlines moved `a[0x3C] = g[0x18]` above the two
  other stores (installed). The near a0l family func_8010FDB4 / func_8010FC58 / func_80110548 (20 words) needs
  retail's early `addiu a0,s0,0x2C` before the store list (not a store order: permlines cannot reach it). Hand
  work from the drafts is still the way (AGENTS.md "Round 10 forms").
- **ccheck.py**: a scratch whose prototypes install_c would drop is compiled a second time that way; `warning: F
  compiles differently with the scratch's prototypes dropped (--no-protos): install_c will produce different
  code (first difference at +0xN)` (tested with a narrow `u8` parameter prototype); `--skip-protos-check`;
  `--sbs --real`.
- **install_c.py**: a scratch prototype with a parameter narrower than int for a callee the target calls elsewhere
  and does not define becomes K&R `T f();` (dropped when the target declares it); typedefs / struct definitions go
  before the prototypes; a linked-build DIFF prints `first difference at 0xADDR (FUNC+0xOFF): ours X, retail Y`
  (build/<prog>.bin against the disc file, symbol from build/<prog>.map). Not done: the false link DIFF of a01
  func_80121678 (extern clash with an s8[] -> alias).
- **regswap.py**: fork never starts at an assignment that reads the variable (`x = x + 1`) or inside a block the
  later uses are outside of; the `const` kind (constants as early locals) only with `--hacks` or an explicit
  `--only`; new kinds `emptycase` (`case K: break;` for missing values next to the labels), `caseinc` (`x = K + 1`
  in `case K` of `switch (x)` -> `x++`), `vstore` (a store through a volatile lvalue: dead stores retail keeps),
  `perarm` (`k = K1; if (c) k = K2; x = k;` -> one store per arm). Tested on a synthetic scratch (each kind
  generated, the `x = x + 1` fork refused).
- **sbs.py `--real`** (also `ccheck --sbs --real`): a `|` row whose only difference is the immediate of a relocated
  field (on either side) is shown as equal. **permlines**: no move past `break;` / `return` / `continue;` /
  `goto` (before, a0l func_80110548 "improved" 20 -> 9 by moving a store after a `return`). **workqueue**:
  `size_hex` csv column (the printed size was already hex). **integrate.py**: removes build/tmp_regswap_* and
  tempfile build/tmpXXXXXXXX older than 2 hours at the start.
- Not done (time box): nearcopy concatenation mode (sop func_8010C26C = a00 func_80115598 + func_80115B88's
  loop), permlines case-block mode / auto-marking, a reload diagnostic, regswap stores through the a0 copy /
  per-store barriers.

## 2026-11-24 (5): tenth round

All code in C: **4625 / 7011 functions (66.0 %, 41.9 % of the bytes)**, from 4486 (39.3 %). main +3, a00-a01 +14 (~11
KB: round-9 near misses finished with `__asm__ volatile("")` barriers and regswap's const-as-local kinds), a02-a03 +31
(a02, ~12 KB: actor state machines and inits), a04-a08 +74 (~31 KB, the best round so far), a09-a0l + overlays +17
(~14.5 KB, among them OPN's camera state machine func_8018AC84, 0xCA0, from 471 words to a match). Phase 3 (boot and
the small overlays) is at 67 % of its bytes. 29 / 29 byte-identical; an intermediate push (d17ec9c) was checked by a
clean build of that commit in a temporary worktree, tools/integrate.py checked the commits after it.

Findings (folded into AGENTS.md):
- **NPC actor state machines of a04-a08** (about 60 left): one skeleton: case 0 init (func_800519E0 / func_80051B70
  + func_80040CDC + a list of stores), case 1 dispatching on a[0x5E] / a[3] / a[5], case 2 empty, case 3 calling
  func_8007A624. Written straight from the retail asm they take 2-4 minutes each and usually match first time. To
  list them: pending functions (still INCLUDE_ASM) whose asm calls func_8007A624 and one of func_800519E0 /
  func_80051B70 / func_80040CDC. Other scopes likely have the same family: check.
- An inline helper returning a flag: `static inline s32 f(...)` with early `return 1;` / final `return 0;`, called as
  `r = f(A); r += f(B); if (r == 2)` (opn func_8018AC84).
- `bne v0,X; li v0,K1 (delay); li v0,K2; L: sb v0`: one store per arm (`if (c) a[f] = K1; else a[f] = K2;`).
- `__asm__ volatile("");` right after a store that retail keeps before a later independent load.
- An inline helper taking a global's address hoists it into a saved register: use a statement-expression macro
  `({ ... })` instead.
- OT linking: `D_800ED8C8[4] = p` is an array store the load of D_800BF544 gets hoisted above: write it as `*(u32 *)(ot
  + 0x10)` through a `u8 *ot` local, one local per link.
- Pitfall: install_c copies scratch prototypes with parameter types narrower than int into the target, which changes
  other callers (link DIFF while ccheck says OK); it drops prototypes of undeclared callees (implicit int): cast their
  results. Run `ccheck --no-protos` before installing; drop narrow prototypes and cast at the call.

Near misses (scratch in the session scratchpad r10b/<scope>/): a07 func_8010A660 1, a05 func_8013484C 1, a01
func_80129394 1, main func_8007AA38 1 instruction, a00 func_80127798 2, func_80118B10 2, a02 func_8010B068 2 (3
copies), a08 func_8013C6B4 2-3, a00 func_8013BCC8 3 (6 copies), a06 func_8011159C 4, main func_80021DF4 4, boot
func_80011654 5, a05 func_8012D908 5, a07 func_8012D2B4 6 (3 copies), a0a f_UpdateEvilPigRushAttack 6 aligned words (6
copies; abs is gcc's abssi2: `m = abs(rr)`, one `move a0,v0` left), a01 f_UpdatePipeAreaScenePropActor 6, a00
func_8011B738 8, main func_80063B94 10, f_RebuildTombaAppearanceModelParts 11, func_8002EF58 11, a02 func_80111640 13,
a08 func_8010D9AC 13, a06 func_8011D520 14, a00 f_HandleKainenHouseQuestItemActor 14, a02 func_8010FBFC 15, main
func_80030264 16, a0a func_801140D0 21 (4 copies), opn func_8018BF08 20, game func_80106A24 19.

Tool work left: an NPC state-machine skeleton drafter (above); ccheck: run the `--no-protos` compile itself and warn
when it differs; install_c: never copy prototypes with narrow parameter types for callees that have other callers (K&R
form instead), place inserted prototypes after the typedefs they use, the first differing offset / relocation on a
link DIFF, the false link DIFF of a01 func_80121678 (extern clash with an s8[] -> alias); regswap: never fork into an
uninitialised variable, reject "hack" rewrites (constants pulled into early locals) unless asked, kinds "emptycase"
(`case K: break;`), "x = K -> x++ in a switch case", "volatile store" for dead stores retail keeps, "one store per
arm" from `k = K1; if (c) k = K2; x = k;`, stores through the a0 argument copy, per-store barriers; permlines: never
past `break;` / return, a case-block permutation mode, auto-mark runs of constant stores; nearcopy: a concatenation
mode (matched A followed by matched body B: sop func_8010C26C = a00 func_80115598 + func_80115B88's loop); sbs.py
`--real` (hide relocation-only differences); a reload diagnostic (spill register per reload, ours vs retail);
workqueue size column in hex; leftover build/tmp_regswap_* of killed runs.

## 2026-11-24 (4): tools after round 9

One tools agent, the "Tool work left" list of the round-9 entry below, in its order (about 60 minutes).

- **regswap.py**: new kinds `keep` (a copy of a local right after one of its assignments, used by every later
  use, or every one but the first: retail's `move a0,v0`, one value in two registers), `callcopy` (a call inside
  a bigger expression into a local, top-level or block-scoped: the call result copied before a shift / abs),
  `barrier` (`__asm__ volatile("");` between two statements), `swapif` (`if (!(c)) {B} else {A}`), `perbranch`
  (the statement after an if / else that uses a local set at the end of both arms goes into each arm with that
  arm's value, the local gone), `ptrlocal` (globals through pointer locals in a block, over 1-4 statements or a
  whole case). `copy` / `keep` apply only where the copy dominates the use (same block or deeper, no case / label /
  reassignment between, no loop back edge with another value; every assignment, not only the first). Multi-
  declarator lines (`s32 a, b;`) are read as locals: they used to end the declaration scan, so on most scratches
  the local-based kinds (decl, copy, fork, reuse, pathsplit, callres) saw only the lines above the first one.
- **ccheck.py**: for another length it prints `score N: K word(s) short / extra, aligned` next to the positional
  count: the number ccheck.score() gives and regswap / variants / permlines report (a0a rush.c: 443 positional, 6
  aligned = regswap's start). A warning per call whose argument count differs from the callee's definition in
  src/<prog>/<prog>.c or src/main/main.c.
- **install_c.py**: comma-separated externs split before the clash check; unused scratch static helpers dropped;
  scratch prototypes of callees with a non-int return that the target does not declare kept (K&R); `#include
  "actor.h"` carried; calls of target functions defined earlier with another parameter count cast. Tested by a
  round trip of a0g func_80109180 with all four in the scratch (file byte-identical but for the kept `u8
  *func_8002300C();` and the include, linked build OK; restored) and the cast on a synthetic file.
- **permlines.py**: `//P` lines move only inside their own block and case segment (regions()); a progress line per
  batch and every 15 s; `--max-seconds`. a01 func_80124F14 (4f14_p.c): 15 -> 3 in 25 s.
- **statemachine.py --cases** (and with every draft): <name>.cases.txt, the retail asm per case block with the
  cases entering it, its range, calls and exits (`case 10 +0x1C`: a shared tail inside another case).
- **tools/loophoist.py** FILE.c FUNC --prog P: cc1 -dL movables (insn, reg, life, savings, moved / not desirable,
  the value) and per loop the constants / addresses loaded before vs inside, ours and retail. a04 func_8013C2EC:
  gcc moves 0x55555555, %hi(D_800ED8C8), 0x5000000, 0x2000000 out of the loop; retail hoists only the three %hi
  and keeps the three constants inside: the near miss is gcc 2.8.1 hoisting the constants (a compiler / flag
  question, not a source order one; try a cc1 variant that does not move constant move-insns, or the loop's shape).
- Near misses with the new kinds: a0a f_UpdateEvilPigRushAttack 5 -> 3 words (`rr_c = rr;` after `rr = r;`, `if
  (rr_c < 0)`; scratch r9b/a09/rushT.regswap.c; left: retail stores the 0x6C field late from the copy, ours in the
  first delay slot), a09 func_8010C01C 8 and a0d func_801108F0 3 unchanged (nothing installed).
- Not done: workqueue same-overlay siblings, nearcopy pairs inside one program, prio.py name mapping, nearcopy
  auto-variant with the scratchpad pointer-local block.

## 2026-11-24 (3): ninth round

All code in C: **4486 / 7011 functions (64.0 %, 39.3 % of the bytes)**, from 4384 (37.3 %). main +16 (~8.9 KB: GPU
load-image packets, actor pool init, Tomba model / cling motion), a00-a01 +22 (~11.5 KB, f_ConfigureSegmentedTownActorMorph
0x830), a02-a03 +13 (a03 from 12 % to 30 % of its bytes: trolley track sampling, models, course progress), a04-a08 +30
(~16.7 KB: conversation / scripted-sequence state machines written from the retail asm), a09-a0l + overlays +20 (~10
KB); nearcopy afterwards +1 (a0k). 29 / 29 byte-identical; tools/integrate.py: all 75 commits link.

Findings (folded into AGENTS.md):
- Three scratchpad globals read in a row with all `lui`s first: pointer locals in a block (`{ s16 *p0 = &D_1F800160;
  s16 *p1 = &D_1F800162; s16 *p2 = &D_1F800164; dx = *p0 - H(a,0x2E); ... }`): took the 6-copy
  f_UpdateEvilPigRushAttack family from ~16 lines to one instruction.
- Strength-reduced pointer registers follow the order of the increments at the end of the loop body and of the
  inits before the loop, not the declaration order (f_ConfigureSegmentedTownActorMorph from 61 words to 0).
- A value stored with different constants on each path: the store with its constant in every branch (one cross-jumped
  `sb`), never a local assigned per branch.
- An empty `__asm__ volatile("");` between statements is a scheduler barrier that emits nothing (keeps constant
  loads in source order in long store runs).
- Wrong callee argument counts are common in m2c drafts: check how matched code calls the callee before blaming
  registers (func_80051B70 takes 3; f_AllocateTemplateEffectSlot and func_80042310 none).
- State machines with nested switches: write them from the retail asm, the statemachine.py drafts come out broken.
- Several near misses are one `move` retail keeps and our compile folds away (the rush family, a09 func_8010C01C, a0d
  func_801108F0): a tool idea below.

Near misses (scratch in the session scratchpad r9b/<scope>/): a0a f_UpdateEvilPigRushAttack 1 instruction (6 copies
of 0x860), a01 func_80117BCC 1, a02 func_8010B068 2 (3 copies), a05 func_8012D908 2 lines, func_8013484C 2
instructions, a0a func_80113B78 2, a00 func_80118B10 2, a01 func_80123BF8 3, func_80124F14 3, a00 func_80120C50 3,
a0c func_8011353C 3, main func_80021DF4 4, a07 func_80120120 5, a00 func_8013BCC8 5 (6 copies), a07 func_8012D2B4 6
(3 copies), a03 f_UpdateTrolleyCourseOverlayActor 7, a0h func_8010A918 7, a09 func_8010C01C 8, a0k func_80117DE8 9,
a05 func_8011105C ~10, main func_8002EF58 11, a02 func_801168A0 11, a04 func_8013C2EC (0x4DC, loop hoisting of
constants; copy a06 func_8013E738).

Tool work left: a regswap / variants kind that keeps a copy in its own register (block-scoped temporary assigned
from the value and used later) for the "one extra move" near misses; a scheduler-barrier kind (`__asm__ volatile("")`
between statements); "store per branch instead of a local", "swap if / else arms", "pointer local per case"; a
loop-hoisting diagnostic from cc1's -dL dump (movables, lifetimes, moved or not); statemachine.py: per-case asm range
and branch targets instead of broken drafts; install_c: drop unused scratch static helpers, keep scratch prototypes
of callees with a non-int return that the target does not declare, carry `#include "actor.h"`, apply the cast
rewrite when a callee is defined earlier with fewer parameters, split comma-separated externs before the clash check;
ccheck: warn when a call's argument count differs from the target's definition; permlines: never move `//P` lines
across case labels, a progress line / time budget; regswap: the copy rewrite only where the copy dominates, its score
equal to ccheck's; prio.py name mapping; nearcopy: pairs inside one program, an auto-variant with the scratchpad
pointer-local block; workqueue: flag same-overlay siblings (ratio >= 0.5) of new C.

## 2026-11-24 (2): tools after round 8

One tools agent, the "Tool work left" list of the round-8 entry below, in its order.

- **asm by design for game code**: `python3 -I tools/asm_by_design.py --game [--prog P] [--write]`. A pending game
  function is hand-written assembly when it has no stack frame and uses instructions gcc 2.8.1 never emits for C:
  the trapping `add` / `addi` / `sub` or `or rd, $zero, rs` moves. No matched game function of any program has
  either (the tool checks this on every run and stops on a hit). The mark is a `// ASM by design: ...` line right
  above the INCLUDE_ASM line in src/<prog>/<prog>.c (sync_src.py keeps it with the line); progress.py counts these
  as done (column "game asm (by design)"), workqueue / nearcopy / inlined.py no longer list them as targets.
  Marked 12: one family of GTE primitive-list builders (rtpt / nclip / avsz3 over a vertex list into the OT, the
  end pointer returned), two per overlay: a00 func_801465EC + f_UpdateWindmillCollapseParticleActor, a04
  func_8013F418 + f_UpdateThirdReadyOrNotKujaraDialogue, a05 func_8013AC90 + f_UpdateThreeSistersCutsceneActorC,
  a07 func_801311D0 + f_UpdateCircusLockerNpcActor, a08 func_80140FBC + f_UpdateWaterTempleRaftNpcActor, a0l
  func_80112DEC + f_DispatchEndingAreaCameraSequence (the imported names of the second of each pair are wrong:
  they are not actor updates). splat's `/* Handwritten function */` header is not a signal on its own: 138 matched
  game functions with GTE macros have it too.
- **install_c.py**: a failed linked build prints the compiler / linker error lines (`file:line: ...`, undefined
  references; first 12) and the NOT INSTALLED reason is the first of them (`linked build DIFF` when it compiles);
  calls of an installed function after its definition (or a full prototype) with another argument count are
  rewritten as `((RET (*)())f)(...)` (checked: the same code as the undeclared call) instead of failing to compile;
  a scratch `#define` the target has with another body is renamed `NAME_xxxx` with a warning; "changed
  config/aliases_<prog>.ld: commit ... too" when the install added alias lines; a type name the install left defined
  twice (identical copies) keeps the first copy only (different copies are reported). Tested: a broken scratch into
  opn (error lines shown, file restored), a macro clash (renamed), a round trip of a0g func_80109180 (removed, then
  installed again: the file is byte-identical), the cast rewrite on a synthetic file.
- **ccheck `--no-protos`** works again: install_c.drop_prototypes() re-joined ptsrc items, which lose the newline
  after a `#include` and the comment above one (`#include expects FILENAME`, lost `// CC` lines); it now cuts the
  dropped prototypes out of the text itself.
- **workqueue.py** re-reads the INCLUDE_ASM lines before it writes the csv and drops what was installed while it ran
  ("dropped N function(s) installed meanwhile"); the `inl` column is flagged when the inlined.py csv is older than
  the last change of src/. Rerun it (under a second for one program) instead of reading an old build/queue_*.csv.
- **nearcopy `--near`**: every near file gets a `// retail diff:` line and the run prints it per target: how the
  source's retail code differs from the target's (`constants only: ...`, `extra N words at +off`, `missing N words
  before +off`, `N -> M words differ at +off`, constants `+off a -> b`, operand / register changes, other callees;
  relocations compared by kind, overlay-local callees not counted). Run on a0b a0c `--ratio 0.7`: a0b func_8010BE38
  8 off <- a01 func_8012B2D8 (2 constants, 2 extra words at +1C, ...).
- **regswap.py**: the wrap and volatile rewrites come first in every round and, past `--max-cands`, every kind takes
  its turn (decl orders alone used to fill the budget of a big function); `wrap` also takes runs of two or three
  statements and the span of one local's uses (never around break / continue / case); new kinds `callres` (`p->x =
  f(a);` -> `v = f(a); p->x = v;` with a local dead there) and `abs` (`abs(E)` <-> `E < 0 ? -E : E`, `E >= 0 ? E :
  -E`, `__builtin_abs`, `if (v < 0) v = -v;` -> abs); splits through a temporary narrower than the store's target
  (they truncate) are dropped unless `--narrowing` (then flagged NARROWING), an unknown target type is flagged;
  `--max-seconds S` stops the search (best text kept). Tried on a0b func_8010BE38 (9 off, nothing better) and
  func_80113F94 (68 -> 65 in 8 s with `--max-seconds 8`).
- **inlined.py `--repeats`** [PROGS]: pending functions that hold one block of code several times (a loop body or a
  helper inlined / unrolled at each use; no matched body needed): block length in normalised instructions (keys
  without immediates), copies, register consistency, immediates that differ between the copies (helper
  parameters), each copy's address range (build/repeats[_<progs>].csv). Under a second for a00: 98 blocks there,
  e.g. f_ConfigureSegmentedTownActorMorph 125 instructions x2 (30 constants differ), func_801234A4 93 x2 (identical),
  func_8013CDD4 39 x4, f_AnimateWindmillCollapseMainSequence 18 x7. It lists, it does not draft the helper: write
  the block once as `static inline` from decomp.py's draft at the first range. Overlapping blocks of one function
  can both be listed.
- Not done (left for a later tools pass): install_c warning on a narrower-than-int return type with implicit-int
  callers, a regswap "const local per use" kind, a helper draft for --repeats blocks, the loop-hoisting diff and the
  scheduling helper (loads hoisted above a store to another global).

## 2026-11-24: eighth round (new scopes, work queue; two container restarts)

All code in C: **4372 / 7011 functions (62.4 %, 37.1 % of the bytes)**, from 4220 (33.1 %). First round with the new
scopes (main; a00-a01; a02-a03; a04-a08; a09-a0l + overlays) and targets from tools/workqueue.py. The container
restarted twice while the agents worked; the disk survived both times, so the committed work did (the agents commit
every function or two), only their reports of the first part were lost; the round was relaunched from the commits and
the scratch files. Intermediate pushes were made only of commits whose clean full build is 29 / 29 (checked in a
temporary worktree); tools/integrate.py checked that all 43 commits after 9db1d81 link. Per scope: main ~30 (the most
called pending MAIN functions: f_PlaySoundEffect, f_RunActorScriptInterpreter, f_BeginScriptedInteractionAudio, the
model-transform and skeletal-animation functions, f_ResolveTombaGroundTerrainContact, f_UpdateTombaAirborneMotion,
...: every caller now has the real prototype), a00-a01 ~16, a02-a03 ~20 (a03 trolley menus), a04-a08 ~55 (~33 KB:
cling orientations, depth-cued GT3 / GT4 lists, effect spawners), a09-a0l + overlays ~35 (triangle grid-cell collector
with 11 copies, f_UpdateEvilPigRelocationAttack with its 5 copies, depth-cued emitters in a0k).

Findings (folded into AGENTS.md):
- `nearcopy.py --near --ratio 0.6`, then hand edits of the differing constants / statements / blocks, was the most
  productive method of the round.
- Two tests sharing one body where retail reloads the global in each: `if (A) {body; return;} else if (B) {body;
  return;}` with the body written twice, not `A || B` (pad handlers; cross-jumping merges the copies after CSE).
- Keeping the first copy of a cross-jumped call: `r = a[0x29] = call(...); test: if (r) goto found; goto end;` on the
  first path, the last path ends `r = ... = call(...); goto test;` (gcc keeps the later copy otherwise).
- Stack-slot sharing for block-scoped struct copies: a local whose address goes to a call stays live to the end of its
  block: declare the shared array in the enclosing scope.
- Jump table with empty cases: distinct dead stores per case keep the labels (gcc merges labels sharing a body).
- A conversion right before a `jal` in the argument register is a cast at the call (`f((s16)z)`); a `u8` return type
  breaks implicit-int callers that test the result (linked build DIFF while ccheck says OK): keep s32.
- Wrong argument counts of callees change scheduling: check how other overlays call the same function.
- Probably assembly by design (no frame, `or t0,zero,a0` moves that gcc never emits, start `beqz a2`): a00
  f_UpdateWindmillCollapseParticleActor, a07 f_UpdateCircusLockerNpcActor, a0l f_DispatchEndingAreaCameraSequence, a08
  f_UpdateWaterTempleRaftNpcActor; the a00 func_801465EC family (no frame, t-registers only). To do: mark them with
  asm_by_design.py (it handles library files: extend it to game functions) after checking.

Near misses (scratch in the session scratchpad r8b/<scope>/): a01 func_80117290 1, func_80117BCC 1, func_8012AC84 1,
a05 func_8013484C 2 instructions, a0c func_8011353C 2 lines, main func_800532A0 3, a0f func_8010A5F8 3 (hoist order;
a0c func_8010B36C), a08 func_8012282C 3 lines, a00 func_8013BCC8 5 (6-copy family), a0b func_8010BE38 5, a0l
func_8010FC58 5 lines (= func_8010FDB4), a02 func_8010B068 6 (3 copies), a07 func_8012D2B4 6 (copies a05
func_8013590C, a08 func_8012A06C), a03 f_UpdateTrolleyCourseOverlayActor 7, f_UpdateTrolleySteeringInput 9, a0b
func_801127BC 12, a01 func_80113D44 14, a04 func_8013D0F8 15, a0a f_UpdateEvilPigRushAttack ~16 lines (6 copies), a07
func_8010D84C 17, a02 f_UpdateTabbyHouseSceneController 25, a0a func_801140D0 25 (3 copies), main
f_DrawPackedGouraudQuadStream ~25 lines, main func_80056F3C 35.

Tool work left: install_c: print the compiler error on a failed link, rewrite callers with another argument count
through a cast instead of failing, warn on a return type narrower than int with implicit-int callers, warn when a
scratch macro redefines one with another body, say when it changed an aliases file, avoid duplicate typedef names
when moving up; ccheck `--no-protos` loses the include path; workqueue.py: drop installed functions (stale csv);
nearcopy `--near`: a diff summary (missing / extra block, constants only, callees); asm_by_design.py for game code;
regswap: `do {} while (0)` wrap and volatile re-read in the first round, const local per use, reuse a local for a
call result, abs variants, flag narrowing splits, `--max-seconds`; inlined.py: a loop body inlined several times in
one function -> one helper; a loop-hoisting diff and a scheduling helper (loads hoisted above a store to another
global); heredocs with inline asm must be quoted (`<<'EOF'`).

## 2026-11-23 (5): speed-up tools

One tools agent (the user approved the list). No function count change.

- **tools/integrate.py**: the coordinator's end-of-round checklist in one command, never commits or pushes:
  `python3 -I tools/integrate.py [--since REF] [--skip-clean] [--skip-sweeps] [-j N]` / `--only-since REF`. Clean
  full build (`rm -rf build asm`, build), a second build, the src/ files the first build's sync_src rewrote (and
  whether the change is whitespace / blank lines only) and whether the second build changed anything more;
  `nearcopy.py --install` and `dupsweep.py --install` over all programs; full build; readme_progress; progress
  --phases; with `--since REF` every commit of REF..HEAD checked out in a temporary worktree (build/tmp_integrate_wt,
  game/ include/pt include/psyq symlinked, `checkout -f` because the build's sync_src rewrites src/) and the
  programs it touched built (src/<prog>/, config/<prog>.yaml / aliases / symbol_addrs; include/, config/*.ld or the
  build tools -> all 29); prints the commits that do not link, `first` when that program built at the previous
  checked commit. A full build is about 1 minute, so a round of ~40 commits checks in well under an hour. Tried:
  `--only-since HEAD~8` (8 commits, 5 touching programs: all link, 1 minute); the full run `--since HEAD~3 -j 4` (3 minutes): clean build 29 OK (55 s), no sync_src change, second build 29 OK and unchanged, nearcopy / dupsweep nothing to install (the round 7 integration had swept), build 29 OK, 4220 / 7011 functions (33.1 % of the bytes), README unchanged, 3 commits all link; the worktree is removed afterwards. Not tried yet: a round with a commit that really does not link (the report path is untested).
- **tools/workqueue.py** (bottom-up work queue; not tools/queue.py, which would shadow the stdlib `queue` that
  concurrent.futures imports for every tool run from tools/): `python3 -I tools/workqueue.py [PROG ...] [--top 30]
  [--min-size N] [--max-size N] [--lib]`. Per pending function: callees (jal targets resolved in the program, then
  MAIN, then boot, by name or func_<address>), how many are pending (named), `ext` (found nowhere), `jalr`, size,
  jump tables, inlined matched bodies (build/inlined_<progs>.csv or build/inlined.csv when present), family (same
  opcodes, any program) and exact copies, callers in the scope. Rank: no pending callee first, then size x exact
  copies. build/queue_<progs>.csv; the last line names the pending callees blocking the most functions. Over all
  programs: 2674 pending game functions; the most-needed pending callees are all MAIN functions:
  **f_PlaySoundEffect (0x280) is called by 521 pending functions**, f_RunActorScriptInterpreter 202, ratan2 173,
  f_BeginScriptedInteractionAudio 161, f_UpdateActorScaledOffsetModelTransforms 158, f_ResolveActorAreaPlanePosition
  135, f_AdvanceActorSkeletalAnimation 121, f_InitializeMultiPartActorModel 109 (main agent: these first; a pending
  callee does not stop a caller from matching, but its real signature and return type are then known). a00-a01: 424
  pending (0x48C04 bytes), 139 (0x140EC bytes) call no pending function; top: f_CollectA00GridCellsInsideTriangle
  0x604 (2 exact copies), f_ConfigureSegmentedTownActorMorph 0x830, a01 func_8013000C 0x82C, func_801234A4 0x7F0,
  f_UpdatePipeAreaMudballSurpriseCarrierActor 0x7D8.
- **include/actor.h** rewritten from a census of the matched C (19k accesses through `a` / `p` pointers:
  `a[0xNN]`, `H(a, 0xNN)`, `*(T *)(a + 0xNN)`, MEMBER_AT): `typedef struct Actor` (0xC8 bytes) with each offset at
  its most used access type (u8 0x00-0x0D with flags / kind / mode a[3] / state a[4] / subState a[5], linked 0x10,
  callback 0x1C, next 0x24, position halves xFrac/x 0x2C/0x2E, y 0x30/0x32, z 0x34/0x36, s16 fields 0x40-0x94,
  parts 0xC0), the Tomba2Edit names kept. m2c gets it through **`tools/decomp.py NAME --actor [--actor-args 0,1]`**
  (and statemachine.py / dispatch.py `--actor`): decomp.actor_context() runs the plain draft, retypes the listed
  parameters of its signature as `Actor *` and appends that prototype to the context (build/ctx_actor/). Scratches get
  `#include "actor.h"` (install_c carries it into the target). Kept optional (a flag): arg0 is not always an actor.
  Effect on 10 pending a00 / a01 state machines (m2c draft as is, ccheck words off / casts): the same words off on 8
  (e.g. f_UpdateKainenHouseWobbleEffect 64 / 24 casts -> 64 / 5, f_AnimateNetBridgeFishIdle 98 / 62 -> 98 / 21,
  f_AdvanceKainenHouseRescueSequence 114 / 43 -> 114 / 17), one better (f_AnimateSmallFishSuspendedMotion 55 -> 54,
  40 -> 9 casts), one worse (a01 func_80117A00 90 -> 103: retail keeps a derived base `s1 = a + 0x60` that the plain
  draft reproduces and the struct draft folds into field accesses; use the plain draft there). The drafts read
  `arg0->state`, `arg0->y`, `arg0->unk_58 += ...` with the right signedness; already-matched C is untouched.

**Proposal (not done): split src/main/main.c (19.5k lines) and the big overlays (a00 8.8k, a01 7.3k, a08 7.6k, a06
6.9k lines) into several C files by address range.** Why: two agents can work one program without touching the
same file, ccheck / install_c / sync_src read and rewrite a fraction of the text, builds compile the parts in
parallel. gcc 2.8.1 at -O2 does not inline across functions without `inline` (no -finline-functions), so each
function's code depends only on the declarations visible to it: splitting is safe when each part gets the same
declarations, static inline helpers and macros its functions saw. Plan:
1. splat: the program's single game `c` subsegment (`[0xD2C0, c, main]`, a00 `[0x13A0, c, a00]`) becomes several
   (`[0xD2C0, c, main_00]`, `[0x1A000, c, main_01]`, ... at function starts; the .rodata / .data subsegments stay as
   they are: game C has no rodata of its own, its switches use the retail tables through tools/jtbl.py). The asm of
   pending functions moves to asm/<prog>/nonmatchings/<part>/, so INCLUDE_ASM lines name the part. Cut points: the
   original object boundaries where visible (alignment padding, a change in rodata use), else every ~150 functions.
2. Shared declarations: the file-scope text before the first function and the externs / prototypes / macros / static
   inline helpers between functions go to src/<prog>/<prog>.h (types, externs, macros) and each part keeps the
   helpers its functions use (a helper used by two parts: in the header as `static inline`). Watch macros redefined
   differently further down (a00 `H` with one and two arguments), prototypes that differ on purpose (K&R definitions
   for callers passing fewer arguments, `T f();` for leftover registers, calls through cast pointers): those stay
   per part. A one-off tools/splitsrc.py does the cut and proves it with a full build (29 OK) before committing.
3. A shared module tools/srcfiles.py: `game_files(prog)` -> [(path, start, end, asm dir)] from the yaml,
   `file_for(prog, name or address)`, `include_asm_line(prog, name)`; every tool below uses it instead of
   `src/<prog>/<prog>.c` / `"asm/%s/nonmatchings/%s"`. Land this first with one part per program (no change in
   behaviour), then split.
Tools that assume one src/<prog>/<prog>.c and what each needs:
- build.py: runs sync_src only when src/<prog>/<prog>.c exists -> once per game part (or sync_src does all parts);
  the split / re-split loop is unchanged.
- sync_src.py: rewrites the one file in address order -> per part over its address range; a C function whose
  address falls into another part after a re-split moves to that part (as it already moves functions into library
  files); renames over all parts.
- install_c.py: target = `src/<prog>/<prog>.c` (line 189) and the INCLUDE_ASM line format (lines 280, 285) -> the part
  holding the function's INCLUDE_ASM; the declarations / helpers / alias logic per part; the per-program lock stays.
- nearcopy.py (Prog.src, Prog.pending, Prog.includes), dupsweep.py (c_functions, the INCLUDE_ASM replacements at lines
  270-290): read all parts, write into the part holding each target.
- ccheck.py (line 131: the target file's declarations for scratch prototypes): the part holding --func, or the header
  plus all parts.
- dispatch.py helpers() (the `/* NAME, inlined */` helpers of the file), statemachine.py (globs: fine), inlined.py
  (globs: fine): read all parts.
- sweep.py, nonmatching.py, libnear.py `--game`, libpermute.py `--game`, t1sweep.py, decomp.py `--write` (glob, but
  INCLUDE_ASM line format): the part and the new line format.
- progress.py, funcstats.py, arity.py, workqueue.py, integrate.py, readme_progress.py: glob src/<prog>/**/*.c and parse
  INCLUDE_ASM by regex: work as they are (check the library test `/psyq/` still excludes the parts).
- install_lib.py, libsweep.py, pzsweep.py, asm_by_design.py: library files only, unaffected.
- config/eu/: no C, unaffected; AGENTS.md / CLAUDE.md lines that say `src/<prog>/<prog>.c`.

## 2026-11-23 (4): Tombi! 1 C against Tomba! 2

Question: can the matched C of the first game (Tombi-Decomp, PAL, fully matched, MIT) be reused here? Its
docs/TOMBA2_DEMO.md had only compared bytes (one identical function, tickTaskTimers). New tool **tools/t1sweep.py**
compiles every T1 game C file with this repo's game pipeline (gcc 2.8.1 + maspsx 2.79, T1's headers in a temporary
build/t1sweep/inc, T2's include/psyq for the Psy-Q headers T1 fetches at set-up) and compares each function by masked
words with every pending function of the 29 programs (same length: words off; lengths within 15 %: difflib ratio).

Result: **no reusable code.** 9244 T1 game files (library range of MAIN0 and per-version copies with a base file left
out), 9217 compiled (9229 functions), 27 failed (version-only files needing T1 headers outside include/, a few
parse errors; not pursued). Best match per T1 function of 8+ words against the 2678 pending T2 functions: 0 within 0
words, 0 within 1-4, 115 within 5-16 (all tiny 10-20 word functions with ratio < 0.6: chance), difflib ratio >= 0.9:
0, >= 0.8: 0, >= 0.7: 1, >= 0.6: 10. Positive control (`--matched`, against all 7011 T2 functions): 92 exact, 86
within 1-4 words, 149 with ratio >= 0.9: the method works, and the code T2 shares with T1 (task / thread helpers
tickTaskTimers, ThreadTableRun, ThreadWaitFrames, initObjectPoolUnlayered, clearMenuState, small animation thunks)
is **already matched** here. T1 was built with gcc 2.7.2, T2 with gcc 2.8.1; the shared helpers compile the same under both.

Installed (+4, now 4220 / 7011 functions; all by hand from the closest pairs): main **f_AdvanceActorTimedFrameSequence** (0xE4, T1's
AnimAdvance with T2's offsets: timer s16 at +0xE, list pointer at +0x38, 4-byte entries; the `case 0` writes the
pointer once and shares the tail with 0x4000; the only T1-derived function, credited in the file and in
THIRD_PARTY_NOTICES.md), and three small actor state machines the sweep pointed at by shape (not T1 code): main
func_80033560, a06 func_80119874, a06 func_80122CAC (each matched at the first try written plainly from the asm).
Verdict: **not worth more effort** as a C source; the only use left is reading T1's C for the
engine's idioms (actor struct, animation lists) when a T2 function looks familiar. t1sweep stays for a re-run if
T1 gains code (it takes ~10 minutes, `--reuse` re-compares the cached keys in seconds).

## 2026-11-23 (3): seventh round of five agents (time-boxed)

All code in C: **4216 / 7011 functions (60.1 %, 33.1 % of the bytes)**, from 4130 (31.0 %). main +12 in two passes
(an actor family func_8006A080..func_8006BB6C, Tomba state machines func_80065A54, func_800702C0,
f_ArmTombaFacingInteraction44), library +9 (_SsClose with gcc-2.7.2-loop4, _spu_FwriteByIO, SsSeqCalledTbyT,
SpuSetReverbModeParam, _SsVmSeqKeyOff, SetGraphQueue main / boot, region func_80012954), a00-a03 +23 (~16.6 KB,
windmill / net bridge cutscenes, a01 state machines), a04-a08 +29 (~13.8 KB), a09-a0l + overlays +13 (~15 KB:
a0l ending camera sequences, f_UpdateEvilPigDefeatAndRewardSequence and its 5 copies). 29 / 29 byte-identical; agents
had about 70 minutes each. Several intermediate commits of this round did not link (alias lines committed later):
always push only after the clean full build.

Findings (folded into AGENTS.md):
- **gcc 2.7.2 gives a for / while loop with a non-constant bound an unused 8-byte frame slot**: write `i = 0; if (n
  > 0) do { ...; i++; } while (i < n);` (the guard must compare the bound with 0; `continue` becomes a goto before the
  increment). A 2.7.2 near miss whose frame is 8 or 16 bytes too big is this case.
- **Division by a field just stored** (`a->40 = K; a->4A = (...) / a->40; a->4C = (...) / a->40;`) gives retail's
  `li K; div` and the `lh` reloads; `la reg, sym+off` followed by stores from that register means gcc 2.8.1
  `-mno-split-addresses`, not 2.7.2.
- A constant from the switch dispatch reused in a shared tail: write the tail in each branch (CSE carries the
  register into each copy, cross-jumping merges them); the opposite (a constant rematerialised after an if): `if (c)
  x = A; else x = B;` with the store in both arms.
- Block-scoped locals for each copy of a repeated inner loop in a big function; camera-script tables are 12-byte
  entries (`&T[H(a, 0x6A)++]`); gcc will not merge an arm with another case's identical code: goto labels inside the
  later case's arms.

Near misses (scratch in the session scratchpad r7b/<scope>/): a01 func_80117290 1, func_80117BCC 1, func_8012AC84 1,
a04 func_8011A8A0 1 instruction, main func_8007AA38 1 instruction, a0l f_UpdateEndingArea5MysteryCameraSequence 2
(order only), CD_sync 3, CD_ready 3 (prologue tie-break), Snd_SetPlayMode 3, a01 func_80124F14 3, a08 func_8012282C 3
lines, _dws 4, _SsVmVSetUp 4, a00 f_HandleKainenInteraction 5, f_UpdateA00InteriorTransitionActor 5, a01
func_80129394 7, a02 func_80112D08 7, a05 func_8012D908 9, a06 func_8011EBD0 9, StCdInterrupt 9, region func_800127E0
11, a07 func_801222A4 13, a0a f_UpdateEvilPigRushAttack 14 lines (family of 6), f_UpdateEvilPigRelocationAttack 15
lines (family of 6), a00 f_RunWinsWindmillCutscene 16, main func_800696C4 17 lines, a04 func_8011C4E0 20, main
func_80066878 29 lines.

Tool work left: ccheck `--no-protos` is broken ("#include expects FILENAME"); install_c: print the first differing
address / function on a link failure, warn when a scratch prototype differs from the target's, say to commit the
aliases file it changed, keep a `// Source:` line (install_lib), check macro redefinitions between the first
definition and the insertion point (a00 `H` with one and two arguments); permlines: keep moves inside the enclosing
block (it moved `//P` lines out of a switch case), a time budget for `--exhaustive`; regswap: semantic checks
(narrowing splits truncate, reused variables), `do { } while (0)` around a variable's uses, block-scope a region,
shared tail -> duplicated per predecessor, `__typeof__` locals never into src/, speed on 0x600+ functions;
statemachine.py: the target file's prototypes instead of m2c's, the exit kind of each case, the div-reload shape,
code shared between sibling state machines, the camera-script family; ccheck / sbs: frame difference in the summary,
scheduling-only marks with a MEMBER_AT hint, a held-constant detector; pzsweep / libsweep: automatic for -> guarded
do/while under 2.7.2, "frame only" near misses; a prologue tie-break and a scheduling-dependence diagnostic; variants
block substitution; prio.py names with array locals.

## 2026-11-23 (2): tools after round 6

One tools agent on the "Tool work left" list below. +2 functions: main `_spu_gcSPU` (0x300, `// CC
gcc-2.7.2-loop4`, the library agent's psyz scratch as is), a06 func_80137148 (0x13C state machine: statemachine.py's
decomp.py draft was 50 words off, every case written in full matched at once). 29 / 29 byte-identical.

Done:
- **Loop-hoisting compilers** in tools/setup_native.sh (copied from the stock directories, sha1 checked before and
  after, same as nocse; session_bootstrap.sh checks them): `/opt/oldgcc/gcc-2.7.2-loop4` (0xC6C66 / 0xC6C6D -> 4,
  sha1 3384800e...), `gcc-2.8.1-loop2` (0xDC87D -> 2, 1f4a6ea4...), `gcc-2.8.1-nocse-loop2` (0204821e...); identical
  to the library agent's copies. libsweep `LOOP_VARIANTS` (`--loop` / `--only-loop`, also in libnear; shared
  `apply_variant_args`), pzsweep `--loop` and `--cc A,B` (only these compilers; an unknown one, e.g. a path, takes
  the set-ups of its stock family). Runs: libsweep `--only-loop --install` main 0 / 174, boot 0 / 73; pzsweep with
  the three compilers 0 matched, near: Snd_SetPlayMode 6 (nocse-loop2 + EPILOGUE sony), _SsClose (main
  func_8008DC00) 7. Hand tries: CD_sync 3 words (loop2 or nocse-loop2, `-mno-split-addresses`), CD_ready 18 (cdr.c
  with `Intr.c = 0;` / `Intr.ready = 0;` before the copies), _SsClose 6 words with gcc-2.7.2-loop4 (from 71): only
  the frame differs (`vars= 8`: 32 bytes for retail's 24, every instruction equal), _SsVmInit 51 (loop4 alone does
  not do it).
- **tools/statemachine.py**: `--list [PROGS]` (pending functions with rodata jump tables, matched-call share,
  switch operand a[N]; MAIN's functions named by address in overlay asm count as matched) and `PROG NAME`: header
  with every table's cases (target, calls, inlined matched bodies), helpers, the closer of the dispatch.py /
  decomp.py drafts (other one in <name>.alt.c). Drafts of 12 small all-matched candidates: 46-98 words off as
  written by m2c; they need the cases written in full by hand (as func_80137148).
- dispatch.py: a helper another helper needs is written once (a06 func_80130F1C now compiles: 356 words off); a
  crash on one function is reported and the rest go on.
- install_c: `extern M2C_UNK func_X;` (or `s32`) for a called function -> `s32 func_X();`, dropped when the target
  declares it. regswap: no MEMBER_AT unless the base is a name / member chain plus a literal. nearcopy `--near`
  alone implies `--ratio 0.8`.

Left: install_c (auto K&R when existing callers pass fewer arguments, alias renames inside moved helpers, a moved
helper's prototypes, forward prototype of a self-referencing function used in a helper above it, typedefs declared
further down -> K&R); regswap semantic check for reused / forked variables; prio.py names with array locals;
inlined.py reverse search; families.py tail-extra variants; statemachine.py: case bodies written per case (each
case's code from the jump target to the next target, cross-jumped tails duplicated) instead of m2c's gotos; the
loop4 frame slot of _SsClose (an unused spill slot, look at reload's frame with loop4); and the rest of the list
below.

## 2026-11-23: sixth round of five agents (dispatchers first)

All code in C: **4128 / 7011 functions (58.9 %, 30.9 % of the bytes)**, from 3925 (26.9 %): the biggest round in
bytes. main +30 (GTE draw dispatchers, cylinder contact code), library +16 (getintr, SsSeqOpen, CdControl / F / B,
CdInit, CdReadSync, region func_80012B9C, ...), a00-a03 +50 (~30 KB, actor state machines), a04-a08 +43 (~36 KB,
state machines up to 0xC8C bytes), a09-a0l + overlays +67. 29 / 29 byte-identical. sync_src.py takes K&R definitions
written on one line. Stray `//-- a` variant separators removed from a05 / a06 / a08 (main.c line ~8192 has a `//--`
comment of the same kind: harmless, remove when next in that area).

Findings:
- **Actor state machines** are the bulk of the medium / large functions left: `switch (a[4])` (sub-switches on a[3]
  / a[5]) whose cases call already-matched handlers. Write them whole: each matched body as `static inline`, every
  case in full, the case table read from rodata (dispatch.py's drafts are poor for these: decomp.py's are better).
  About 3 minutes each when the handlers are matched. The pending asm calling func_800518FC / func_8007A624 with a
  low memory-op ratio is a good list of them.
- **List walkers** (a09-a0f): a fixed template over the scratchpad lists 0x1F80013C / 148 / 14C / 154 with counter
  D_1F800182 (AGENTS.md); 16 matches this round.
- **The library compiler hoists more loop invariants around loops with calls**: patching the `loop_has_call`
  multiplier in scan_loop (gcc-2.7.2-psx cc1 file offsets 0xC6C66 / 0xC6C6D, `mov $1/$2,%edx` -> 4; gcc-2.8.1
  0xDC87D / 0xDC884) makes CdControl / F / B and _spu_gcSPU match as is; every other matched 2.7.2 loop file still
  matches except CD_cachefile, so it must be a per-file set-up (like nocse). With the stock compiler the same code is
  reached by hand (`m1 = -1;` at the end of the do/while body, a long-lived `int one = 1;` before the loop): that is
  how CdControl / F / B are in. To do: `gcc-2.7.2-loop4` / `gcc-2.8.1-loop2` set-ups in setup_native.sh (sha1
  checked) and in libsweep / libnear / pzsweep.
- **Reload spill registers** in GTE functions are the call-clobbered registers no pseudo uses, in order: make the
  rest of the function allocate retail's registers and the spill cycle follows.
- 4.4 libcd ReadAttr at D_800AC2E4 (boot D_80026BF8): {u0, u4, addr, mode, size, nsec, u18, u1c = start_time, cnt =
  pos, done, cbsync, cbready, cbdata, result}; the region module is partly gcc 2.7.2 (try it first there).

Near misses (words off; scratch in the session scratchpad r6b/<scope>/): a01 func_80116294 1, a05
f_UpdateKujaraSummitQuestPickupActor 1 (retail keeps a second `beqz p`), a0b func_8010B73C 1 / a0a func_80118038 6
(clamp copy: retail compares the source after `move a0,v0`), region func_80012954 1, a0e func_80117600 2, CD_sync 3,
Snd_SetPlayMode 3, _spu_FwriteByIO 3, a0a func_8010A3D8 / a0c func_8010B36C / a0f func_8010A5F8 3 (hoist order:
counter `lui` before the invariant), a01 f_UpdateCapperActor 4, func_80115F08 4 (and its dispatcher
f_UpdatePipeAreaScenePropActor 4), main func_8007A464 4, func_80021DF4 4 (prologue save order), SetGraphQueue 4, _dws
4, sop func_8010A0E0 4, _spu_gcSPU 6 (matches with the loop4 compiler), _SsClose 6, main func_8007F104 6, a08
func_8010B9FC 6 lines, CD_ready 7, a06 func_8010B59C 7, a08 func_8012282C 7, main func_8002E458 8, a01
f_UpdatePipeAreaQuestSceneryActor 11, func_8010F87C 11, main func_80035528 / func_800355B4 14 (exact priority tie).
Untouched dispatchers with good bodies: a06 func_80130F1C (0x734), a08 func_8010D334 (0x678).

Tool work left: the loop4 / loop2 compiler set-ups (above) and pzsweep `--cc`; an actor state-machine generator
(rodata jump tables -> switch skeleton, matched case bodies as static inline helpers, sub-switches on a[3] / a[5],
common tails); a list-walker generator; dispatch.py: duplicate helper definitions, m2c crashes on its drafts, a
rodata jump-table mode; install_c: auto K&R when existing callers pass fewer arguments, apply alias renames inside
moved helpers, keep the prototypes a moved helper needs, forward prototype of a self-referencing function used in a
helper above it, prototypes with typedefs declared further down -> K&R, `extern M2C_UNK func_X;` -> function
declaration, the helper move-up that broke a link; regswap: semantic check (no use of a reused / forked variable
after reassignment, no MEMBER_AT with a variable offset), "per-case local" and "copy used only in the last call";
prio.py: names shifted when array locals are not pseudos, a tie mode; a spill-register predictor for GTE functions;
a hoist-order diagnostic; inlined.py reverse search (a pending function identical to an existing helper); families.py
tail-extra variants (sop func_80109FE0, a0d func_80113628, a0e func_80114320, a0l func_8010B0B8); variants.py `--set`
placeholders inside `--alts` blocks; sbs.py: relocation annotations on literal `lui` values; a frame-slot tool for
inlined helpers' stack arrays (a06 func_80129C50); nearcopy `--near` default ratio.

## 2026-11-22 (10): paused after the round-5 tools pass (where to pick up)

The user stopped the cycle before a sixth round. State at the pause: **3925 / 7011 functions in C (26.9 % of the
bytes)**, 29 / 29 byte-identical, everything pushed to master. To resume: run `bash tools/session_bootstrap.sh`, read
AGENTS.md ("Order of work", "Parallel rounds"), and start a sixth round of five hand-matching agents on the usual
scopes with the tools of (9): dispatch.py first (106 pending dispatchers of matched bodies: a08
f_UpdateClosedClamshellQuestActor is 20 words off, scratch was in the session scratchpad r6/clam.c), then families,
inlined bodies, the near misses of (8) and (9), then medium / large functions. Most bytes left: the big areas a00-a08
(18 % of their bytes), MAIN (30 %), the medium areas (35 %).

## 2026-11-22 (9): tools after round 5

One tools agent turned the "Tool work left" list of (8) into tools, each tried on real functions. +5 functions
(**3925 / 7011, 26.9 % of the bytes**; 29 / 29 byte-identical): a00 f_HandleTownQuestRewardVisualActor (0x430, 4 inline helpers, from a dispatch.py draft at the
first try), a01 func_80121BAC (0x3A8, 4 helpers, one `s16` decrement), main func_80050738 (regswap member toggle),
a06 func_80124AA0 (regswap parameter copy; install_c needed the K&R fix below), a02 func_8010CFAC (the a07 copy: it
failed to link because a02.c had `void func_8010CFAC(void);` for its use as a value; install_c now rewrites such a
prototype to the definition's header).

Done:
- **`tools/dispatch.py`**: `--list [PROGS]`: pending functions in which inlined.py finds 2+ matched bodies at
  places that do not overlap (106 now; most covered first). `PROG NAME ...`: build/dispatch/<prog>/<name>.c, a ready
  install_c scratch: each body as a `static inline` helper headed `/* NAME, inlined */` (the target's own helper
  when it has one; declarations transitively; symbols of another program's body renamed through the aligned
  `%hi` / `jal` operands; a differing constant patched when its literal is unique) and the caller skeleton: m2c
  (`--valid-syntax`) on the pending asm with every inlined span replaced by `jal helper` (parameters moved from the
  saved register the copy keeps them in, the result moved where the copy leaves it, conditional exits kept as
  `beqz $v0`), so the draft reads `inl_X(arg0);` per case. Header notes: register maps, spans, exits that make the
  helper value-returning, and **labels inside a span reached from outside** (a tail gcc cross-jumped with other
  code, or a case entering the copy: that path is missing from the skeleton; write it out in full). Then ccheck.
  Matched 2 of 4 tried at once or after one fix; a08 f_UpdateClosedClamshellQuestActor 20 words (registers: a in
  s2 instead of s1; prio.py says `m` outranks `a`), f_UpdateWaterTempleQuestItemPickupActor drafted (outer cases
  fall into the next one: needs hand work), a04 func_8013E910 / a05 func_80114CC8 compile (118 / 109 off).
- **inlined.py**: `search()` reusable (dispatch.py uses it), csv `build/inlined_<progs>.csv` for a scope run
  (build/inlined.csv only for all programs: no overwriting between agents), a `consts` column / `{op:K->K2}` in the
  listing: immediates that differ between the body and its copy at the same place (patch the helper or pass the
  value as a parameter).
- **regswap.py** new rewrites: `temp` (each parameter copied, after or before the declarations, and all at once),
  `load` (a read moved into a local before the previous store, or to the top when it only uses parameters and
  globals), `const` (a literal as an early s32 / u8 / s16 local, one use or all, or set just before its use),
  `member` (`*(T *)(p + o)` / `M2C_FIELD(p, T *, o)` <-> `MEMBER_AT(T, p, o)`, now in include/common.h, and file
  macros of that form back to casts), `volatile` (one read as `*(volatile T *)&(e)`), `goto` (a goto replaced by a
  copy of its tail), `ternary` (<-> if / else), `pathsplit` (a local renamed to the end of its if arm / case, only
  when its value does not flow out); `--skip`, `--max-cands`. On 20 near misses of (8): 2 matches (main
  func_80050738 5 -> 0 member, a06 func_80124AA0 4 -> 0 temp), a05 func_8010B5E8 8 -> 3 (member), a06 func_8010B59C
  10 -> 7 (const), main func_80035424 46 -> 15 (load + const); the 1-3 word ones did not move.
- **prio.py** `--prog P`: a `retail` column (the register retail uses where ours uses each hard register, the
  instruction lists aligned) and, for every pseudo in another register, which pseudo holds the wanted one and with
  what priority (raise ours above it, or the choice is a tie / conflict). `--sched`: the function's insns in output
  order (cc1 -dp uids) with the block and priority sched / sched2 gave them. **ccheck.py** says `order only` when a
  DIFF function has retail's instructions in another order (relocated fields masked) and points to `--sched`.
- **`tools/pzsweep.py`**: psyz (/opt/psyz/decomp/src + the Psy-Q 4.0 SDK headers /opt/psyz_inc/og, which
  setup_native.sh now makes from psyz's psyq400.tar.gz, sha256 checked) and psy-q-decomp (`-DVERSION=40`) as
  sources: every file of a library the project has, preprocessed whole (`-DPERMUTER` drops its INCLUDE_ASM), compiled
  under 26 set-ups (`--all-variants`: 72), every function compared (masked) with every pending library function of
  main / boot of the same size whatever its name; a match is cut standalone (pzcut logic: types, inline helpers,
  prototypes, externs, strings -> D_ symbols), checked alone, written to build/pzsweep/<prog>/ with its set-up and
  `// Source:` line, `--install`ed with install_lib. Full run (main + boot, 1136 files, ~4 min with -j 3): no new
  match (round 5 took them); near misses listed (asm-by-design files and functions under 0x20 bytes left out):
  only Snd_SetPlayMode 8. 28 psy-q-decomp libsnd files do not compile (conflicting prototypes in the sources
  themselves), listed by the run.
- **install_c.py**: a clashing extern uses an alias of that address the target already declares the same way
  (else a new hashed alias, listing the target's other names for the address); a prototype taken from a definition
  further down stays K&R (`T f();`) when a call passes fewer arguments; a target prototype of an installed function
  with other parameters becomes the definition's header; kept prototypes naming a type nobody defines become K&R.
  **install_lib.py split()**: a struct with function-pointer fields is named by its tag / typedef, `extern T *a, *b;`
  declares both names. **nearcopy.fix_names** prints a symbol that gets two addresses (in one function, from the
  relocations, or between functions) instead of skipping it silently (libsweep.reloc_symbols(conflicts=)).
- Smaller: variants.py `--set` values take `\&` (and a backslash before any punctuation) as the literal character;
  decomp.py prints `/* decomp.py: F at ADDR: a2 not written on every path to the call ... */` for calls whose m2c
  arguments include registers no path writes since the entry or the previous call (a guessed argument, or a
  parameter passed through).

Near misses after this round (scratch in the session scratchpad r6/rs/): a05 func_8010B5E8 3
(func_8010B5E8.regswap.c), a06 func_8010B59C 7, main func_80035424 15, a08 f_UpdateClosedClamshellQuestActor 20
(r6/clam.c, clam.regswap.c), plus the unchanged ones of (8).

Tool work left: dispatch.py could write the cross-jumped tails itself (the code at a shared label inside a span,
from the plain m2c draft) and the outer-case fallthroughs; regswap on the 1-3 word near misses found nothing
(they need statement moves or types: combine with permlines / hillclimb); prio.py --sched does not map insns to
the retail words (the `-dp` uids are per cc1 insn, maspsx expands some); pzsweep near misses of libsnd / libpress
(func_8008C260 6 from DecDCTReset, Snd_SetPlayMode 8) by hand with the 4.0 -> 4.4 list.

## 2026-11-22 (8): fifth round of five agents

All code in C: **3920 / 7011 functions (55.9 %, 26.8 % of the bytes)**, from 3686 (23.1 %). main +38 (the GTE
projection family of 5 with shared inline helpers), library +42 (39 + SpuSetCommonAttr x2 / SsSetTickMode once
jtbl.py learnt the bare-operand jump table; most adapted from psyz and psy-q-decomp, MIT, now in
THIRD_PARTY_NOTICES.md and cloned by setup_native.sh), a00-a03 +46, a04-a08 +54, a09-a0l + overlays +53 (tower
contact dispatchers, big a0k / a0l actors). 29 / 29 byte-identical. AGENTS.md is new: the distilled method and recipe
catalogue (keep it current with CLAUDE.md, the user's standing instruction). sync_src.py keeps declarations placed
just above an INCLUDE_ASM line. a02 func_8010CFAC (copy of a07 func_8010F954) matches in ccheck but not in the link:
look at its symbols.

New recipes (folded into AGENTS.md):
- **Inlined handlers**: 25 of a00-a03's 35 hand matches and most big functions of a09-a0l are switches / sequences
  of already-matched functions copied as `static inline`, several per function. A helper returning through a local
  adds a `move`: write that body out. Scratchpad pointers and loads as locals inside a parameterless inline helper,
  with the same dead pointer locals declared in the callers (GTE projection family).
- **Struct-member access** (non-QImode) never aliases a fixed scalar global in gcc 2.8: `S16F(p, o)` struct-member
  macros to keep a global load above the stores, and a global accessed as a struct member
  (`D_800BF870.pad1[0x143]`) to keep its store in place.
- **Copy the parameter to a local** (`void f(u8 *a0) { u8 *a = a0; ...}`) when the argument and a derived pointer
  have swapped saved registers (func_800281EC 16 words -> OK); check for dead copies in regswap / permuter output.
- **Sony's single exit**: `__asm__ volatile("");` before the closing brace (library).
- **Library 4.0 vs 4.4**: `_svm_voice` 0x38 bytes (s16 at 0x1A and 0x36); SeqStruct l_count / unk21..23 / vab_id
  signed char (`!= -1`); `(s8)_svm_cur.fake_program`; _SsSndStop has no SsUtReverbOff; SpuClearReverbWorkArea
  `size = 0x400; if (length <= 0x400) { size = length; last = 0; }`; SsVabTransBody tests SpuSetTransferStartAddr;
  _SsNoteOn has no voll check; Snd_SetPlayMode `s8 play_mode`, `_SsVmSetSeqVol(..., 1)`; SpuInit's loop runs down
  with a pointer; `volatile flush *p = &D; p->c = 0; p->b = p->c; p->a = 2;` for CD_flush / CD_init; `extern s32
  D_x[]` (not char[]) for strings copied by __builtin_memcpy.
- **Smaller**: `if (x) call(); k = 0;` for a value set in a delay slot and again after a call; `move t0,v0` after a
  test = the field re-read; scratchpad pointer set after an early return moves its `lui`; speed tables as u16 fields
  into u32 locals `(u32)((s16)x * 19) >> 4`; `s16 k = -0xA00; x = k - y`; clamp with a copy `if (u >= 0x80) v =
  0x80; else v = u;`; `e[i * 4 + k]` for a single pointer.

Near misses (words off; scratch in the session scratchpad r5b/<scope>/): a0b func_8010B73C 1, a01 func_80116294 1,
region func_80012954 1, main func_80059ED8 2, func_800726D4 2, a01 func_8012B464 2, func_801206D8 2, a00
func_80118B10 2, a0b func_8010A3D0 2, a0k func_801147D0 ~2 lines, func_8008C260 2, main
f_ClassifyActiveColliderPartCylinderContact 3, a00 func_8013BCC8 / a04 func_8012379C 3 (the 6-copy family: lui of
D_1F800137), Snd_SetPlayMode 3, a06 func_80124AA0 4, _dws 4, SetGraphQueue 4, _SsVmVSetUp 4, SpuRGetAllKeysStatus 4,
main func_80050738 5, a0e func_80117600 5, _SsSetControlChange 5, main func_80035338 6 (and twin func_80035424 41:
the parameter must get s0), f_StartCooperativeWorker 7, a08 func_8012282C 7, a08 func_8010A660 8, a05 func_8010B5E8
8, main func_8002E458 8, a06 func_8011CEDC 9, StCdInterrupt 9, a06 func_8010B59C 10, a06 func_80129218 11, a0a
func_801140D0 21 (3 copies), a07 func_8010D0B4 22 (3 copies), a03 f_UpdateTrolleyRetryMenu 24 (3 copies).

Tool work left: regswap: "copy parameter to a local" per parameter, "read field into a local before the previous
store", "constant as an early local", cast <-> struct-member toggle, volatile re-read, goto -> duplicated tail,
ternary -> if/else, split shared temporaries per path; ccheck: allocno priorities (refs, live length) next to
retail's register order; a dispatcher drafter (inlined.csv: one pending function covering several matched bodies ->
switch skeleton with static inline copies); inlined.py: ready scratch output, copies with other offsets / constants,
per-scope csv names; install_c: name clashing externs and suggest the existing alias, no prototypes with undefined
typedefs or K&R conflicts; install_lib split(): structs with function-pointer fields, `extern T *a, *b;`;
nearcopy.fix_names: report a symbol that gets two addresses; libsweep: psyz / psy-q-decomp as sources (whole-file
compile, masked compare against every pending function); variants.py: `\&` literal; decomp.py: flag guessed call
arguments; a sched-priority hint (-dS) for order-only diffs.

## 2026-11-22 (7): tools after round 4

One agent turned the round-4 "tool work left" list into tools, each tried on real functions. +14 functions: main
f_ClassifyActorCylinderContact, func_8007B18C, func_8007703C, f_TryApplyTombaActorDamage, func_80031F84 (a nearcopy
near miss: `scale[i]` without `* 4`), SpuMalloc (libsweep --only-nocse, psx_tomba's C); a01 func_80127298 (K&R);
a05 func_801297EC, func_80130AFC, func_8012E340 (regswap) and its a0b copy func_801144F4; a06 func_80131BE8,
func_80131CD4, func_80130D98.
- **`tools/inlined.py`** (known inline bodies): every matched function's normalised instructions (nops, moves,
  prologue / epilogue gone; relocated immediates, branch and $sp offsets masked; registers free) searched in the
  pending functions of all programs: 674 hold a copy (cover >= 0.8; build/inlined.csv, smallest first, with the
  register consistency and the `/* NAME, inlined */` helper src/ already has). Recipe that matched 10 of the above
  at once or nearly: copy the matched C as `static inline` with that comment, call it where the copy is (a
  `return 0` becomes the caller's branch); a `case` falling into the next one when retail has no `j` after it.
  Many more candidates at cover 1.00 / r1.00 (a07 func_80125E40, a08 func_8012282C, a0f func_8010AF60, a00
  func_80116E3C, a06 func_80124AA0, a0a func_80114B38, main func_8004A118, the f_SetEffectProjectionTransform
  family func_80027CB4 / 80027E5C / 8002801C / 8002DBE4 / 800286CC, ...). The cylinder test (f_TestActorCylinder*)
  is inlined in 9 pending contact functions, not ~20 (the others call SquareRoot0 / ratan2 for terrain).
- ptsrc.items(): K&R definitions are one item; a pp line after a comment line stays a pp item (the
  `// nearcopy: N words off` line of installed near-miss scratches had glued `#include` lines and the next type
  into one code item: 15 game files had stray includes inside, a0j a duplicate T2PolyGT3A / T2PolyGT4A; cleaned).
- install_c.py: static helpers behind a comment are helpers; one the target has (same text) is not repeated or
  moves up, a different one is renamed; helpers after the scratch's declarations; K&R definitions (a needed
  prototype is `T f();`); every failure ends `NOT INSTALLED: names (reason)`. install_lib.py: K&R, the library
  file's own includes kept, no common.h beside psyq_all.h / pt/common.h, extra FLAGS (-fno-builtin) kept on every
  set-up, NOT INSTALLED line.
- nocse: libsweep / libnear `--nocse` / `--only-nocse` (NOCSE_VARIANTS: 36 set-ups), `--names`; hillclimb
  `--setup 'CC gcc-2.8.1-nocse;AS gnu'`. libsweep --only-nocse: main SpuMalloc, boot nothing. libnear --only-nocse
  (<= 0x180): SpuGetVoiceVolume 3 (m2c, -O2 -G0 -mno-split-addresses, AS gnu, RETURN sony: 2 left, `x - 0x8000`
  compiles to `addu` of 0x8000 where retail has `subu`), func_80089194 3. By hand: CdControl is closest with
  psx_tomba's `loop()` inline under gcc 2.7.2 + ASPSX (13 lines: -1 kept in s8, constant 1 in t0, normal
  epilogue), 73 words under nocse; func_8009BE9C 3 (the second test's value in v0 in retail, v1 here: no source
  form found). CdControlF / CdControlB / CD_init / func_8008DC00 not retried.
- **`tools/regswap.py FILE.c F`**: greedy register-choice rewrites (declaration orders, store through a
  temporary, reuse / fork / copy of locals, `do { } while (0)` wraps, parameter copies; pairs when no single one
  helps). On the 21 round-4 near misses: a05 func_8012E340 matched (a wrap); the 1-5 word ones did not move.
- nearcopy.py: each occurrence of a repeated constant alone, slti / sltiu K+1 also as literal K (case bounds,
  clamps), `li K` vs a folded `addiu rs,K2` (variable + K2), constants inside the static helpers the body uses,
  `--lib` (library files main <-> boot: nothing new, the copies were done). sbs.py: splat's `(0x1F80xxxx >> 16)`
  operands are relocations (no false `|` lines). permlines.py `--exhaustive` (every order of <= 7 marked lines).
  variants.py: `\|` in --set values, `\t`, and --cc / --flags / --as / --aspsx / --epilogue / --return.
  families.py: a scopes column and `--by-scope` (47 of 120 families span several agent scopes). **`tools/prio.py
  FILE.c [F]`**: pseudo priorities floor_log2(refs) * refs / live_length, block / global, calls crossed, hard
  register, user variables named in declaration order (cc1 -dl -dg). sonyret: `// RETURN sony thread` (a branch to
  a one-insn `j ret; li v0,K` block goes to the return with the insn in its delay slot; opt-in, also in the
  libsweep variant lists).

Near misses from this round: main func_80027CB4 2 lines (the GTE projection family of 5: retail rematerialises
`&D_1F800080` just before `gte_stflg` with its `lui` hoisted to the top; scratch r5/main/7cb4.c),
f_ClassifyActiveColliderPartCylinderContact 10 (d lives in a2 then s4: `ratan2(-dz, dx, d)` does not do it),
func_8004A2A0 3 (`li a0,22` in the delay slot of the second test: the message id choice), boot/main CdControl as
above. Scratch files: the session scratchpad r5/.

Tool work left: inlined.py could write the helper + caller scratch itself (the copy's offsets / constants
patched) and hand it to ccheck; regswap does not change types or move statements (combine with permlines);
nearcopy `--near` hint for a missing / extra block; hillclimb transforms (u8 -> s32 switch variable, call in both
arms with swapped branches, re-read a stored field); a Sony-compiler hypothesis for CdControl (-1 hoisted out of
the loop, 1 in a t register: neither gcc 2.7.2 nor 2.8.1 does both).

## 2026-11-22 (6): fourth round of five agents (families first)

All code in C: **3672 / 7011 functions (52.4 %, 22.9 % of the bytes)**, from 3405 (18.6 %). main +50 (GTE matrix
family, actor pool allocators, ~30 collision / cylinder functions with the inlined tests as `static inline`
helpers), library +12 (and 6 RotMatrix* asm by design), a00-a03 +57, a04-a08 +64, a09-a0l + overlays +76 (the two
9-copy GTE draw-loop families of a0a-a0j and the Evil Pig scene families); nearcopy afterwards +2 (a07). 29 / 29
byte-identical. Starting from tools/families.py worked: most matches came with their copies.

Decisions taken this round (the user asked not to be asked): the licensed-region module at the end of boot.c
[0x80011A0C, 0x80012D2C) is 9 files in src/boot/psyq/region/ (built with the library compiler, so it counts as
library code; not a known Psy-Q library). **gcc-2.8.1-nocse**: Sony's library compiler has no post-reload CSE pass
(`reload_cse_regs`): the library never shows `move a2,a1` for two zero arguments, `sllv` with a register holding 16,
`and x,v0` with v0 = 1 or the deleted redundant moves. tools/setup_native.sh makes /opt/oldgcc/gcc-2.8.1-nocse from
the stock cc1 (one byte at file offset 0x13F026, the entry of reload_cse_regs, becomes `ret`; sha1 checked before
and after); files ask for it with a `// CC gcc-2.8.1-nocse` line. SsUtSetReverbFeedback and region func_80012584 /
func_80012674 match with it. Candidates with the same pattern: CdControl, CdControlF, CdControlB, CD_init (main and
boot), func_8008DC00, func_8009BE9C (3 words), func_80089194. sync_src.py now takes K&R definitions as C items.

New recipes (add to the ones below):
- **Register priority** (gcc 2.8 local-alloc): priority = floor_log2(refs) * refs / live_length (from the `-dl` /
  `-dg` dumps); wrapping a statement in `do { } while (0)` counts its refs more and stops sched from moving
  increments into load-delay slots; this matched the GT4 draw loop at once. Declaration order of temporaries decides
  the registers of mult results; store through a temporary (`y = m1 >> 8; D = y;`) fixes a lui/srl swap; reuse the
  C variable for a derived value (`sx = -sx + 0x98;`) when retail reuses the input register; a separate temp per
  path and one statement per product in sin/cos math.
- **GTE draw loops**: private macros (the `.word` command without nops, packed vertex loads `lw $12; lwc2; mtc2;
  srl $12,16; mtc2`, one `swc2` per SZ); scratchpad pointers as locals `s32 *flg = (s32 *)0x1F800000`.
- **Inlined functions**: many contact functions inline a matched test (`addu a0,zero,zero` result then `bnez a0`):
  write a `static inline` copy of it (main's cylinder test is inlined in ~20 more pending functions: func_8001EC3C,
  func_8001F054, f_ClassifyTombaActorCylinderContact, f_ClassifyActiveColliderPartContact, ...).
- **Calls**: leftover a1/a2 at a call: call with fewer arguments, or pass the extra value as a 3rd argument through a
  K&R prototype (ratan2 keeps SquareRoot0's result in a2); the function's own unused parameter as default return;
  `if (x == 0) f(0x62); else f(0x61);`: the arm order picks beqz/bnez; a K&R definition with narrow parameters stays
  compatible with an existing s32 prototype.
- **Switches**: a global stored in every case gives per-case `lui; li` with one shared `sh`; `s32 s = a[4]` (u8 adds
  an andi), constants in the stores; explicit if/goto where gcc will not build retail's tree; `case 2: break;` for
  `beq 1; slti 2; beqz; bnez`.
- **Scratchpad**: base locals `s = D_1F800000;` with call arguments `D_1F8000D0 + 0x28` give retail's derived bases
  (`addiu s0,s0,-20`); `s32 *sp = &D_1F800084;` keeps the `lui` in a saved register across calls; read values into
  locals in the order retail loads them.
- **Misc**: compare order sets registers (`x > sum` vs `sum < x`); `(r & 0xFF) == 0`, `(a ^ b) == 0`; lhu + sll/sra
  means the u16 was read before an aliasing store and sign-extended after it; `u8 c = a[5]; a[5] = c + 0xFF; if
  (c == 0)`; a local struct copy of a rodata table for a 16-byte copy loop; `__asm__ volatile("nop")` for a nop at a
  branch target; base+offset of D_800BF870 through a struct cast; separate loop variables for nested loops; psx_tomba
  inline helpers as static inline in libsnd; `s32 pad[2]` after a volatile local fixes 2.7.2's frame size.

Near misses (words off): a04 func_8012379C 3 (6-copy family a00 a01 a04 a06 a08 a09: the `lui` of D_1F800137), a00
func_8013BCC8 5 (6-copy 0x3F4 family: v0/v1 in `pad1[0x1A8] |= 1 << k`), a0a func_801140D0 15 (3 copies, registers
only), a0a func_80111B68 28 (4 copies); a01 func_80116294 1, a02 func_80127678 1, a01 func_801206D8 2, a04
func_80110A30 2, a05 func_8012E340 2 (a0b copy), demo func_80106824 2, a0a func_80113A20 2, a0c func_8011353C 2, main
func_8003511C 2, func_80056E08 2, func_8003F3F4 / F4C4 3, func_8007AA38 3, func_80035640 3, a04 func_801351B8 3, a05
func_801155A4 3, a0e func_8010A0C0 3, a04 func_801193D4 4 (= a06 func_801160D4), a00 func_80145CD0 4, func_80111A00 4;
library stopIntr 1, SpuRGetAllKeysStatus 1, func_8008C260 2, func_8009BD84 2, region func_80012954 1. Scratch files
are in the session scratchpad (r4b/<scope>/).

Tool work left: install_c sometimes leaves a moved typedef in place ("conflicting types": a0j now has T2PolyGT3A /
T2PolyGT4A beside T2PolyGT3 / T2PolyGT4, a cleanup item) and should place `static inline` helpers after the externs
they use, parse K&R definitions, and end with a clear "NOT INSTALLED" line; install_lib.py does not parse K&R
definitions or `#include "psyq_all.h"` + `-fno-builtin` files (installed by hand this round); a "known inline body"
detector (a matched function's instruction sequence inside pending functions, with register renaming); a
register-swap search (declaration orders, temporaries, renames) for 1-12 word near misses; nearcopy: try each
occurrence of a repeated immediate, constants in static inline helpers, `li K` vs folded `addiu -K`, case values and
min/max compares, a "block missing / extra" hint for `--near`, library files between main and boot; sbs: do not mark
relocation-only lines; permlines exhaustive mode for <= 7 lines; variants.py: an escape for `|`, multi-line values,
set-up overrides (--cc/--flags/--as/--epilogue/--return); nocse set-ups in libsweep / libnear / hillclimb; sonyret:
thread a branch into a `j ret; li v0,K` block; families.py: mark families spread over several agents' scopes; a
prio.py (pseudo priorities from the cc1 dumps); hillclimb: `do {} while (0)` wrap, variable reuse, u8 -> s32 switch
variable, call in both arms with swapped branch order, re-read a stored field.

## 2026-11-22 (5): tools after round 3

One agent turned the round-3 "tool work left" list into tools (each tested on real functions):
- **`// RETURN sony`** (tools/cc.py, tools/sonyret.py): Sony's library compiler had no `return` insn: every `j $31`
  but the last one branches to the last, which becomes `jr ra; nop`; a jump that falls into it goes; a branch
  over a return is threaded to it (`bne ...,ret; li v0,1`, also when reorg had stolen the target's first insn).
  `// RETURN sony first` also puts an early `if (bad) return -1;` block back after its test (libsnd), its
  body's return value after the body's last load. Usual set-up: gcc 2.8.1 `-O2 -G0 -mno-split-addresses`,
  `// AS gnu`. Installed: memmove, strcmp (main, boot), SsSetReservedVoice, SsUtSetDetVVol (`sony first`),
  StFreeRing (main, boot; the loop store as `s32 k = (i + idx) * 32; *(s16 *)((u8 *)base + k) = 0;`), and by
  libsweep StGetNext (main, boot). boot func_80011A0C matches with it too (below).
- Library installs: `libsweep.py / libnear.py --epilogue` (EPI_VARIANTS: the EPILOGUE / RETURN sony set-ups;
  header() writes those lines), libnear skips files whose INCLUDE_ASM names another function, and
  **`tools/install_lib.py FILE.c [--prog P] [--auto] [--dry]`**: each function of a scratch into its own library
  file with the set-up header, declarations / static helpers it uses, names renamed from the relocations, install
  lock, build check. libsweep --epilogue over main / boot found StGetNext only; libnear --epilogue: no new
  distance <= 2 except _SsContPanpot 2 (m2c, -fno-delayed-branch, AS gnu).
- install_c.py: a type the target has (same text up to layout) is skipped or moved up from further down; one it
  defines differently is renamed (`Name_xxxx`) and reported, never dropped; prototypes of functions the target
  defines further down are kept (written from the definition's header); calls with fewer arguments than a kept
  prototype / an installed definition are reported; a clashing non-D_ global gets an alias from its known
  address; `#include "psyq/inline_c.h"` becomes `#include "gte.h"`. `ccheck.py --no-protos` compiles a scratch
  with the prototypes dropped the same way; ccheck also takes `--epilogue` / `--return`.
- nearcopy.py: alias lines for any name the program does not define (other programs' `D_..._hash` aliases,
  library names) instead of an undefined symbol; a one-word `move` / `li K` difference tries each variable use as
  K (or each literal as a variable). Over all programs (`--max-diff 16 --ratio 0.85`): 12 candidates, no match
  (closest a02 func_80126EA8 5 <- a0a func_80112F0C). permlines.py: orders that move a line across one it depends
  on (variable read / assignment) are not tried (`--unsafe` for the old search); no more race on equal texts.
  variants.py `--alts K=FILE`: `{K}` takes each `@@`-separated block (multi-line alternatives).
- **`tools/families.py`**: pending functions of all programs grouped by opcode sequence, sorted by copies x
  size (build/families.csv): 167 families of 2+ (425 functions, 0x35300 bytes); the top ones are 6-9 exact copies
  of 0x2A0-0x3F4 bytes across a0a-a0f / a00-a06 (one hand match each gives the rest through dupsweep).
- **`include/gte.h`**: includes psyq/inline_c.h (DMPSX placeholders) and redefines its 65 command macros with the
  real cop2 words (rtps 0x4A180001, rtpt 0x4A280030, nclip 0x4B400006, avsz3 0x4B58002D, avsz4 0x4B68002E, dpcs
  0x4A780010, mvmva 0x4A400012 + sf/mx/v/cv/lm: rtv0 0x4A486012, rtir 0x4A49E012, ...; the ones retail uses
  checked against the asm). main, a01, a04, a0k include it instead of psyq/inline_c.h. The GTE recipe below
  ("redefine per file") is obsolete: `#include "gte.h"`.
- hillclimb.py: new transforms (round3_candidates): `default:` first / removed, `x = K + 1` -> `x++` in `case K`
  (x the switch expression), `*(T *)0x1F80xxxx` -> extern `D_1F80xxxx`, top-level early-return inversion.
  Run on the m2c drafts of a04 / a00 / a05 up to 0xC0 bytes (25 functions, `--rounds 4`): no match; closest a04
  func_801351B8 7 (37 from the draft), a00 func_80132548 11, a04 func_8011187C 15, a05 func_801155A4 18.

Left: boot func_80011A0C matches with gcc 2.8.1 `-O2 -G0 -mno-split-addresses`, `// AS gnu`, `// RETURN sony`
(also gcc 2.7.2 AS gnu), not with boot.c's game set-up, so it needs its own file. It is the first function of a
module [0x80011A0C, 0x80012D2C) at the end of boot.c (9 functions: BIOS region byte 0xBFC7FF52, a message screen
with Krom2RawAdd / libgpu, shared globals D_80025454 / D_800384A4; func_80012B08 matches with both set-ups) that no
Psy-Q signature covers. Splitting needs a layout decision (not done): either the 9 as per-function files under
src/boot/psyq/<dir>/ (counted as library, installable with install_lib.py; `- [0x220C, c, psyq/<dir>/func_80011A0C]`
... in config/boot.yaml), or a second game file for the module (tools assume one src/<prog>/<prog>.c). Also left:
SsUtSetVVol (return parts match, register use differs: vc copied to a3 first), SpuGetVoiceVolume (returns match;
retail keeps `andi 0xFFFF` and `subu` of 0x8000: 5-6 words), nested bool returns in hillclimb.

## 2026-11-22 (4): third round of five agents

All code in C: **3396 / 7011 functions (48.4 %, 18.2 % of the bytes)**, from 3034 (15.2 %). main +51, library +51
(34 main, 17 boot; Phase 1 now 76.3 % / 38.5 % B), a00-a03 +60, a04-a08 +118, a09-a0l + overlays +82. nearcopy and
dupsweep over all programs afterwards found nothing more (the agents ran nearcopy inside their scopes). 29 / 29
byte-identical. New in tools/cc.py: `// EPILOGUE sony` (the library's epilogue: nothing in the `j $31` delay slot,
`lw ra; addiu sp; jr ra; nop`; most libsnd / libspu / libgpu functions with a frame want gcc 2.8.1
`-O2 -G0 -mno-split-addresses`, `// AS gnu` and this line), and the jump-table filter now runs on the `AS gnu` path.

New recipes (add to the ones below):
- **Switch state machines**: `default: return 0;` as the first case (or no default at all) gives retail's
  `beqz; beq 1 (v0=0 in delay); j epilogue`; `a[4]++` instead of `a[4] = K` when K is the case value + 1 (gcc reuses
  the register of the next compare constant); two cases with the default value: `case 0: case 1:`.
- **Bool returns**: make `return 1` the shared exit (a break to a final `return 1`, or nested ifs with it innermost)
  with early `return 0`s: `li v0,1` in a delay slot instead of slt/xori. `u8 one = 1` keeps `return 1` its own `li`.
  An early `return -1` placed before the body: `if (ok) { ...; return 0; } return -1;` or `goto err`. `if (i >= n)
  return X;` first, else gcc puts the short return block first.
- **Loads first**: read scalar globals / scratchpad values into locals at the top (`s32 v = D_1F80009C;`) when retail
  loads them before a run of field stores (matched ~8 functions); volatile scratchpad accesses keep source order.
- **Globals**: scratchpad as extern symbols (D_1F80xxxx), not `*(T *)0x1F80xxxx` (`lui at` vs a shared %hi); a
  struct-typed scratchpad extern (`extern SVec3T D_1F8000C0;`) for `sh %lo(sym)` then `addiu base; sh 2(base)`; one
  field through the symbol and the others through `v = &G;` for the same pattern; `&D_80140D38[0x40]` instead of the
  next symbol re-emits the `lui`; a second buffer symbol declared as its own extern, not `&buf[10]`.
- **Registers**: a separate C variable per path when retail shares a register between paths; reusing a variable
  (`p = f(p, k);`) moves it to a lower s-register; `u16 c = id & 0xFF;` stored plus `id & 0xFF` as the index splits
  registers like retail; a u8 flag passed on: `s32 f`, test `!(f & 0xFF)`, pass `(u8)f`; s16 (not u16) locals for
  truncated constants (`li -1024`); `g = f() << 4` instead of `* 16`; constants in saved registers around a loop as
  locals assigned at the top of the loop body; values left in a1/a2 at a call: pass them as extra arguments to a K&R
  or cast callee.
- **Loops**: `D[i].lo` inside the loop (the reduced pointer is set up after the other initialisations); for retail's
  pointer at the last stored field: `s16 *d` stepped `d += 18`, positive indexes, `if (n == 0) return; i = 0; do
  {...} while (++i < n);`; empty countdown loops are real code.
- **Primitives**: addPrim / setaddr / setlen with the bitfield tag `struct { unsigned addr:24; unsigned len:8; }`
  reproduces the `& 0xFF000000 | & 0xFFFFFF` sequences (MAIN candidates: pending asm with `lui 0xff00`, e.g.
  func_8003EA88, 8003E264, 8003E894, 8003E030, 8003EBE0, 8006D654, 8003E448, 8002E680); `TERM_PRIM` with a local
  pointer.
- **GTE**: include/psyq/inline_c.h has placeholder command words; the real ones are rtps 0x4A180001, rtpt
  0x4A280030, nclip 0x4B400006, avsz4 0x4B68002E (redefine per file for now); use the offset macros `gte_ldv3c` /
  `gte_stsxy3_g3`; DQA/DQB loads need custom asm (`ctc2 %0,$27`).
- **Library**: libsnd's parameter copies come from a `static inline` helper shared by SsSeqSetVol / SsSepSetVol /
  _SsSndSetVol; `ch` as s32 fixes the `addu` order of `programs[ch]`; printf keeps fmt on the stack with `char **pf
  = &fmt;`; GPU queue indices `_qin` / `_qout` are volatile s32; magicdiv found 129 (SsUtGetVVol) and 504 (StFreeRing).
- **Misc**: builtin `abs()` gives `bgez/negu`; an unused `s32 pad[2]` declared first fixes a frame size; m2c locals
  set only in some cases are often incoming parameters; permlines.py matched about ten 2-7 word near misses (check
  that its order does not use a variable before it is set).

Near misses (words off): main func_80041938 1, func_80063098 1, func_8003511C 2, func_80056E08 2, func_8003F3F4 /
func_8003F4C4 3, func_8007AA38 3, func_8006DF88 4, f_NewGameSetDefaultValues 4, func_80059ED8 5, func_80050A80 5;
a00 func_80111A00 4 (4 copies), f_BeginScriptedBarrelRotation 5, a01 func_801205E4 7, a02 func_8011F028 9;
a07 func_80125D68 2, a04 func_80110A30 2, func_801351B8 3, a05 func_801155A4 3, a06 func_8011C974 3, func_8013D568 4,
a05 func_8011105C 5, a08 func_8012E61C 5; demo func_80106824 2, a0a func_80113A20 2, a0c func_8011353C 2, a0c
func_80117AC8 3, a0e func_8010A0C0 3, boot func_80011654 5; library func_80089194 2, SsUtSetReverbFeedback 2,
_SsVmSeqKeyOff 3, CdInit 5, _dws 6, SpuGetVoiceVolume 6, _SsContPanpot 7. Match only with `register ... asm("v0")`
(not installed): a0b func_8010BE38, main func_80035528 / func_800355B4. boot func_80011A0C matches with gcc 2.7.2 +
AS gnu: it looks like a library module in boot.c and needs its own file.

Tool work left (from the agents): a "Sony return" rewrite for leaf functions (retail branches to one final
`jr ra; nop` where gcc 2.8.1 emits separate returns: memmove, strcmp, SsSetReservedVoice, SsUtSetDetVVol, StFreeRing);
libsweep.header() and an install tool for library files that write `// EPILOGUE`; libnear.py skipping files whose
INCLUDE_ASM names another function; install_c: skip an identical typedef defined further down, rename / report a
clashing one, keep prototypes of functions defined later, warn about too-few-argument callers; ccheck option to drop
prototypes as install_c does; nearcopy: write needed alias lines instead of refusing other programs' alias names,
map callee names through relocations, patch `move`/`li` form changes; permlines must not move a statement above
the assignment of a variable it reads; variants.py file mode (alternatives split on `@@`); a "families" report
(pending functions of all programs grouped by masked opcodes, copies x size); hillclimb transforms (default case
first, `= K` -> `++`, nested bool returns, scratchpad constant -> extern, early return); a fixed GTE command header.

## 2026-11-22 (3): the round-2 prototypes as tools

One agent turned the hand-matching agents' scratch scripts into tools (each tested on real functions):
- `tools/nearcopy.py [PROG ...] [--install] [--ratio 0.8 --near]`: every pending function against the matched C of
  every program (same length within max(8, 25 %) masked words; `--ratio`: other lengths by difflib, near misses
  only), compiled in its place with patched constants / offsets and renamed symbols, installed through install_c.
  Over all programs it found 2 (a05 func_801154B8 / func_801154D8, one-digit hex literals dupsweep did not patch):
  only 13 pending functions are within 16 structural words of matched C now, so its use is after new hand matches.
  `--near` writes the closest C of the others to build/nearcopy/<prog>/near/ (37 with --ratio 0.8, 1-25 words off:
  a00 func_801230A4 1 (matched, below), a0a func_8010B9AC 4, a00 func_80115B88 5, a05 func_8010E5A8 5, a09
  func_8010A060 5, a0c func_80117B84 5, a0f func_8010DF5C 5, a07 func_8011D410 6, ...).
- `tools/sbs.py FILE.c FUNC --prog P` / `ccheck.py --sbs`: side-by-side diff, branch targets through the alignment.
- `tools/permlines.py FILE.c FUNC --prog P`: moves the `//P` lines (single moves, then pairs; `--slots`); it matched
  a00 func_801230A4 from nearcopy's 1-word near miss (the store is not in retail).
- `tools/variants.py FILE.c FUNC --prog P [--set 'k=a|b']`: words off of each `//--` variant.
- `tools/magicdiv.py MULT --shift S [--unsigned]`: the divisor of a magic-number division.
- install_c.py renames symbols from the relocations (C copied from another overlay installs as is); m2c gets the
  program's jump tables (746 pending jump-table functions now draft; no new as-is matches, hillclimb on the 36
  under 0x140 bytes: none, closest main func_8007AA38 8 words); libsweep: extra set-ups and `#define` renames
  (boot ReadTIM, ReadTMD installed; main rcos matches but changes the link).

## 2026-11-22 (2): second round of five agents

All code in C: **3028 / 7011 functions (43.2 %, 15.2 % of the bytes)**, from 2296 (8.8 %). Agents per scope: main
+40 (jump-table switches, render-queue wrappers), Psy-Q library +214 (Phase 1 now 70.2 % / 31.3 % B: ~170 in C, 44
marked asm by design), a00-a03 +147, a04-a08 +162 (~60 of them variants of C matched elsewhere), a09-a0l + overlays
~+163 (53 by hand, crd 35 -> 55 % of its bytes; ~110 copies by a fuzzy copier); then dupsweep +6 and the fuzzy
copier over all programs +2. 29 / 29 byte-identical. sync_src.py now leaves `static inline` helpers and multi-line
`#define` bodies alone (crd.c has the CRD menu helpers at the top: a static inline must be defined before its first
use, else gcc emits it as a function).

Psy-Q library: three compiler set-ups libsweep.py never tries (each match uses `// FLAGS` / `// AS` lines):
1. gcc 2.8.1 `-O2 -G0 -mno-split-addresses`, ASPSX 2.79: most of libgpu, libcd, libspu, libc2 (without the flag gcc
   hoists `lui %hi` out of loops);
2. the same plus `-fno-delayed-branch` with `// AS gnu`: void functions ending `lw ra; addiu sp; jr ra; nop` and
   functions jumping to one shared exit;
3. gcc 2.7.2 with `// AS gnu`: most of libsnd, libpad, the libcd/libetc statics (`-O1` once, `_padSetVsyncParam`).
Neither is exactly Sony's: 2.7.2 adds a spurious 8/16-byte frame to some loops with a return inside; 2.8.1 turns
jumps to the epilogue into returns. psx_tomba candidates with Tombi's `D_` addresses are kept by mapping each name
with `#define OLD NEW`; pending statics are tried against every psx_tomba function of the same library (found
`_otc`, `_reset`, `get_tw`, `_spu_write`, `startIntr`); MAIN <-> boot C is ported by aligning relocations. Tomba 2's
libsnd score struct is 0xB0 bytes, not psx_tomba's SeqStruct (read_pos +0, play +0x14, channel +0x17, rpn +0x18,
vab_id s8 +0x26, panpot[16] +0x27, programs[16] +0x37, lvol/rvol +0x58, vol u16[16] +0x60, total +0x88,
delta_value +0x90, flags +0x98). libc2 strings are `s8`. Hardware state: a volatile struct through a local pointer.

New recipes (add to the ones below):
- **Constants and CSE**: `n = 3; a[9] = n;` stops gcc reusing an older register holding 3; `s32 k = 3;` used across a
  call keeps it in a saved register; `one = 1; if (x == one)` puts the constant where retail has it; comparing with
  the field just stored (`if (D < a->pad[8])`) re-materialises the constant like retail.
- **Store / load order**: gcc 2.8 does not move a store through a plain pointer cast (`*(u32 *)((u8 *)p + 4) = v;`)
  across a scalar global load, but moves a struct-field store; a store written after the copy of a field stays below
  its load (anti-dependence); write the statement whose value retail loads first earlier in source. Brute-forcing
  the order of a few marked statements (single moves, then pairs) found many matches in seconds.
- **Field reads**: a union of arrays (`union { u8 b[N]; s16 h[N/2]; }`) lets CSE keep a field across stores to other
  fields (M2C_FIELD casts force reloads); `*(T * volatile *)(a + 0x3C)` reloads a pointer twice like retail; reading a
  just-stored byte back (`f(p, p[0x7B])`) gives `andi` of the stored register; `x * 32` keeps `lh` where `x << 5`
  gives `lhu`; `*(s32 *)(p + 0x34) >> 16` gives `lh 0x36`.
- **addu operand order**: `a->arr[i]` / `T *t = D; e = &t[i];` puts the base first (base loaded before the index
  arithmetic); `(u16 *)(idx * 2 + (s32)tbl)` or a precomputed `k = i * 0x3C; (e + k)[4]` puts it second.
- **Registers**: an unexplained `addu a3,a1,zero` is a narrower second variable (`s32 k = load; u8 j = k;`, test zero
  on k, the cases on j); s-registers swapped between a parameter and a pointer: copy the parameter to a local
  (`u8 *a = a0;`); a u8 parameter kept in its own register: declare it s32 and write `port &= 0xFF`; switch result in
  a stack slot: `volatile s32 r`; `abs()` on an s32 avoids re-extension.
- **Control flow**: inlined helpers with early returns: `r = 0; goto done;` per exit (one `move v0,zero` / `move
  a0,zero` per exit); a bool copied to v0 at a switch join: `t = r; break;` in every case plus `default: t = r;`;
  `if (p != NULL) { ...; return p; } return NULL;` keeps v0 and gives the spawners' bnez layout; ternaries that store
  in both arms need an if/else; a constant store retail keeps in two blocks: write it (and the calls) in both
  branches; gotos to shared stores for a multi-exit tail; a goto loop (`loop: ... if (++i < n) goto loop;`) has
  nothing hoisted and no strength reduction; `while (c) {}` instead of `do {} while (c)` re-materialises the `lui`
  in the exit test; retry loop `do { e = alloc(); if (e) goto found; i++; } while (i < 3);`; `switch (x) { case 0:
  x++; ...}` folds `x + 1` to 1, `if (x == 0)` does not; one `&&` condition keeps one basic block so a call reuses
  the incoming a0/a1; `case 0: default:` for a table whose entry 0 is the default label.
- **Calls**: a call where retail leaves the switch-compare register in a0 is called with no arguments; call result
  tested in v0: `if ((*(T *)(a + off) = f()) != NULL)`; store to a global first and pass the global for a late
  `andi a1`; install_c drops prototypes, so cast arguments that need s16 conversions.
- **Globals**: a struct-typed extern alias for a global that needs base+offset in some cases only;
  `*(s32 *)0x1F80009C` instead of the extern when the `lui` placement differs; locals sit at increasing stack offsets
  in declaration order (give arrays their real sizes); register saves before local array stores: aggregate
  initializer `s16 ids[2] = {..}`; repeated tails (message boxes, card events): a macro or static inline helper.
- **Misc**: GTE commands as `__asm__ volatile (".word 0x4A780010")` (dpcs) with `mtc2`/`swc2`; constant divisions:
  brute-force the magic number to find the divisor (2300, 597, 600); branch-free `sltiu` where retail branches: give
  the inline helper a `u8` return type.

Near misses (words off; the agents' scratch files are in the session scratchpad only, not in the repo): main
func_8004DF94 1, f_InitializeTransientEffectActor 1, func_8003511C 2, func_80035528 / func_800355B4 4 (match with
`register ... asm("a2")`, not installed), func_8003F3F4 / func_8003F4C4 3, func_80059ED8 5, func_8007C940 2;
a00 func_8012E7EC 1, a01 func_8012E5F8 2, a00 func_80111A00 4 (4 copies), a01 func_80111CCC 4, a00 func_8012E678 7,
a01 func_80112B10 7, a03 f_UpdateTrolleyRetryMenu 11 (3 copies), a01 func_80119C4C 11 (= a00 func_80145EA4);
a04 func_8013CCDC / func_8013CD78 / a06 func_8014013C 7, a07 func_8011DF48 5, a05 func_8011105C 5, a06 func_8013D568
4; demo func_80106824 2, game func_80107E20 7, a0g f_PlayCourageTowerStreamedAudioSegment 8 (3 copies), crd
func_8018D26C 14; library _SsSndReplay 1, _SsContResetAll 1, memmove 1, SsUtSetReverbFeedback 2, func_8008C260 2
(main and boot), strcmp 2 (2.7.2 frame only), SpuFree 2; rcos and func_8008831C match alone but fail the link.

Tool fixes from the agents' prototypes. Done: install_c.py holds the program lock over the whole edit and merges
alias lines, moves up an extern the file declares further down, aliases type clashes, keeps a scratch file's
`static inline` helpers, and renames symbols named after another program's addresses from the relocations
(nearcopy.fix_names()); ptsrc.items() skips comments; dupsweep.py carries macros, helpers and the types a body
uses; tools/nearcopy.py (near copies: several sources per key, patched immediates and load/store offsets,
relocation renames, `--ratio --near` for hand work); libsweep.py: the three set-ups above and `#define` renames;
decomp.py (and sweep / hillclimb / libsweep / permute) pass the jump tables to m2c; tools/sbs.py / `ccheck.py
--sbs`; tools/permlines.py (`//P`); tools/variants.py (`//--`); tools/magicdiv.py (division magic numbers);
hillclimb: constant into a local, narrow-type copy variable for a switch, guarded do/while <-> while, volatile
field read. Still to do: an isolated-worktree build option for install_c; libsweep: pending statics against every
psx_tomba function of the same library (the agent's cross.py) and MAIN <-> boot ports by relocation alignment;
hillclimb: struct-ify a store, narrow copy variables outside switches.

## 2026-11-22: five parallel hand-matching agents

All code in C: **2296 / 7011 functions (32.7 %, 8.8 % of the bytes)**, from 1543 (4.8 %). Five agents worked at
once on disjoint programs (main; a00-a04; a05-a08; a09-a0f; a0g-a0l + boot/game/demo/opn/sop/crd): 76 + 179 + 197
+ 103 + 112 functions, then `tools/dupsweep.py` put 84 more into the overlay copies. 29 / 29 byte-identical.
Parallel work rules that worked: one program set per agent, `build.py <progs> --no-split` only, no tools/ edits, each
agent commits its own paths with `git commit -- <paths>` (a shared index otherwise mixes agents' staged files), the
coordinator verifies the committed HEAD in a separate worktree (symlink game/ and include/pt, include/psyq) and pushes.

Recipes the agents found (add to the ones below):
- **Cross-jumping**: gcc 2.8 -O2 merges identical tails. Write each case / branch in full (a store repeated in every
  case, a call in both arms of an if/else with one argument different) and let gcc merge them; duplicating case
  bodies is also how to get a jump table where gcc made range compares.
- **Switch layout**: the source order of the cases is the block order; an empty `case 2: break;` (or the missing
  cases of a 0..N table) gives the `beq K; slti K+1; ...` decision tree; GNU case ranges `case 0xC0 ... 0xD0:`
  reproduce range tests; `s32 s = a[k]; switch (s)` in two statements lets gcc reuse the register as a constant.
- **gcc 2.8 aliasing (MEM_IN_STRUCT_P)**: a scalar global is assumed not to alias an array or struct-field access at a
  varying address. Retail reloads a global after a store -> access it as an array element / struct field; retail
  hoists a global load above a pointer store -> make that store a struct field.
- **Base + offset of a global**: `addiu base; lw 0x48(base)` needs a struct-typed extern or a local pointer
  (`u8 *g = D_800E7E80;`); a u8 array with M2C_FIELD folds to `%lo(sym+off)`.
- **Narrow parameter types**: a parameter only stored as a byte -> `u8` (no andi appears) fixes s-register order of
  spawners; a parameter copied at entry whose uses are all masks is u8.
- **Callee prototypes**: a `void` prototype for a callee that returns a value changes scheduling around the call
  (give it the real return type); when main.c's prototype has another argument count, call through a cast function
  pointer `((void (*)(s32))f)(x)`; a K&R prototype reproduces callees that receive a register untouched.
- **Loops**: `e++` and `p[i]` give different strength-reduced pointers, try both; `do { } while` with separate index
  and pointer; `return *p++;` for a pop.
- **Values**: `u8` counters sharing a zero; `d = K; d -= G; d -= n;` for `K - global - local` with the global loaded
  first; `u32 r = x & 0x200; return r != 0;` for andi+sltu; split range checks into nested early returns (gcc folds
  `x < A || x >= B`); a constant set before an if/else stays in a saved register; `x0 = x2 = v` stores x2 first.
- **GTE**: the "handwritten" area functions starting `addu t0,zero,zero; ... ctc2 t0..t2,$21..$23` are psyq
  `gte_ldfcdir(0,0,0)` (define it as an `__asm__ volatile` with three "r" operands; load the scratchpad target into
  a local pointer before the asm). `#include "psyq/inline_c.h"` macros match; an "m"-constraint `gte_ldv0m` gives
  `lwc2 $0, off(reg)`. install_c.py drops `#include` lines: add them by hand.
- **Struct copies from an extern** (aligned: lw/sw, byte struct: lwl/lwr) reproduce local array initialisers without
  new rodata; an unused `s32 pad[4]` gives a 0x10 frame on a leaf.
- **ccheck masks relocations**: two globals of the same type in swapped positions still show OK; the linked build
  (install_c) catches it.
- Near misses left by the agents (1-25 words) are listed in their reports; the most valuable: a0g func_8010C2A4
  (9 copies, 25 words), a02 func_80127034 (8 copies, 3), a09 func_8010D7D4 (8 copies, 43), main func_8007566C (1).

Tool fixes done after the round: hillclimb's hoist transform opens its own `{ }` block, it prints each function's
score as it goes and tries void -> s32; jtbl.py treats adjacent `$L` labels as one address; install_c.py keeps a
scratch file's extra `#include` lines (after the target's), accepts 2-D array externs and restores the aliases file
when the link fails; tools/build.py takes a lock per program (build/.lock_<prog>), so two agents may build the same
program in turn. Still to do: hillclimb transforms (empty case, early-return inversion, pointer/index loops,
extern <-> constant address, duplicated tails); dupgroups.py
should group immediate-only variants as dupsweep does; a ccheck side-by-side mode (objdump of ours next to retail);
a statement-order permuter for marked lines (agents' scratch: perm.py, perm_stmts.py, variants.py).

## 2026-11-14 (3): jump tables in C, NON_MATCHING equivalent C

- **Switches with a jump table can go to C** (`tools/jtbl.py`, called by `tools/build.py` through `cc.compile_c(...,
  asm_filter=)`): the compiler's own table is dropped from the assembly, the code is pointed at the retail
  `jtbl_<addr>` that stays in the program's rodata, and the case labels get the global `.L<addr>` names that table
  refers to (the same names `jlabel` gives them in asm). The table is found by shape (length and which entries are
  equal) among the retail tables whose labels fall inside the function. Measured before: 878 pending functions
  (824 KB, about a third of the pending bytes) use a jump table. `tools/ccheck.py` needs nothing (it ignores
  relocated fields).
- **Decision (user, 2026-11-14): the project stays byte-matching only**; no NON_MATCHING blocks in src. The tool below
  is kept for later but not used.
- **Equivalent C behind NON_MATCHING** (`tools/nonmatching.py FILE.c [--prog] [--note]`), for the native port: the
  function goes in `#ifdef NON_MATCHING <C> #else INCLUDE_ASM #endif`, so the matching build keeps the retail asm.
  The tool refuses a function that matches, checks the matching build and that the file compiles with
  -DNON_MATCHING. The C is not verified byte for byte (the comment says how many words differ): it has to be tested
  in the port. `tools/install_c.py` replaces the whole block once the function matches; `tools/sync_src.py` keeps the
  block with its INCLUDE_ASM line; `tools/progress.py --phases` shows the bytes "with equivalent C" in a last column.

## 2026-11-14 (2): Phase 2 under way (user chose B: engine first, library in parallel)

All code in C: **1532 / 7011 functions (21.9 %, 4.7 % of the bytes)**; Phase 2 MAIN 419 / 1167 (36 %); Phase 4
areas 711 / 4816; library 393 / 867 (incl. asm by design). 29 / 29 byte-identical. `python3 -I tools/progress.py --phases` gives the per-phase table.
- Late in the session: MAIN hand batches of 5-6 functions of 20-35 instructions (smallest INCLUDE_ASM first, skipping
  jump-table switches and the handwritten GTE ones) land about 70 % on the first or second try.
- **Best lever at the end of the session: copies.** Area overlays carry many copies of the same function; one written
  by hand is then installed in every program by `tools/dupsweep.py --install` (it renames the callees and globals to
  each program's names and takes every declaration of the source file). `tools/dupgroups.py` picks the targets:
  group the pending functions by masked word sequence (as funcstats) and take the groups with most copies and few
  bytes. Example: func_80146478 (permuter-assisted) went into 14 programs at once.
- `tools/install_c.py` cannot take K&R definitions yet; callers that pass fewer arguments than a new prototype
  (m2c drops pass-through ones) then fail to compile: give those callers the full argument list instead.
- Every overlay and boot is now a splat `c` segment (`src/<prog>/<prog>.c`), swept like MAIN.
- Sweep (`tools/sweep.py`) improvements, each measured: compilable m2c drafts (`--valid-syntax`, `include/m2c.h`);
  scratchpad variables as symbols (`config/scratchpad.ld` defines every D_1F8xxxxx; drafts declare
  `extern s8 D_1F8xxxxx[]`); missing leading parameters filled; volatile-globals variant; clashing global types go
  through linker aliases (`config/aliases_<prog>.ld`); **parameter counts guessed from the asm** (`tools/arity.py`) in
  m2c's context, so pass-through arguments are kept (the biggest single gain after --valid-syntax).
- Hand decompilation: ~90 MAIN functions, written in scratch files and installed with `tools/install_c.py FILE.c`
  (replaces INCLUDE_ASM lines, adds the declarations before the first use, aliases clashing globals, leaves
  prototypes out because asm drafts call functions with m2c's argument counts). Recurring fixes, worth trying first:
  a global/scratchpad store that must not move into a delay slot -> `volatile`; constants loaded in the wrong order
  -> hold them in local variables (`u32 end = 0xFF`); a base+offset access the compiler folds -> struct field or
  array element; branch layout -> swap the if/else or early return; argument registers passed through untouched ->
  give the function all four parameters; three `lw` + three `sw` through one base (also an argument spilled to its
  home slot and reloaded after a call) -> a struct copy (`Vec3` passed or assigned by value); `v = (x == K) ? 0 : 1`
  turned into `sltu` while retail branches -> still open (func_8001CBA8).
- Script-state steps (`switch (p[0x78])`: case 0 sets up and advances, case 1 waits) match with the shared
  `return 0` as a label inside the switch: `case 0: ...; goto end; case 1: if (done) return 1; end: default:
  return 0;` (func_800425FC, func_8004201C). When case 0 sets the state to 1 and retail reuses the register
  that held the compare constant, the source was `p[0x78]++` (gcc knows the value is 0 there): writing `= 1` or
  `s32 one = 1` gives a v0/v1 swap (func_80117EC8 and its 7 copies, func_8006585C, func_8003A3E8).
- More recipes from this session: a global read that retail does before a run of stores -> read it into a local
  first (the stores might alias it); a callee that receives the caller's argument untouched (`jal` with no
  `move a0`) -> pass that argument explicitly, or call with no arguments when the K&R declaration is in use
  (f_ResolveEffectEightByteStreamPayload(a)); `p = *x; *y = p; if (p == 0)` instead of re-reading; a 0x20-byte
  frame larger than the code needs -> an unused local of that size; a `goto` into the shared `return 0` /
  `*start = 0` tail of an if-chain (f_GetPauseMenuEquipmentGroupRange); an array member of a struct (`->parts[i]`)
  for `base + index` operand order.
- A scratch file that matches can still fail once installed when main.c has no prototype (or a K&R one) for a
  callee whose prototype in the scratch file narrows an argument (s16): cast the argument in the call instead.
- A `switch` whose jump table sits in MAIN's shared rodata does not link once the function is in C (the table's
  `.L` labels vanish): leave such functions in asm until rodata is migrated per function.
- Headers: `include/game.h` GameState (itemCounts at +0x244, appleBits +0x544, flag words), WorkerState,
  CameraState (`g_CameraState`, a linker name for 0x800E8008), PopupRequest / PopupDisplayEntry, MessageBank;
  named scratchpad variables in config/undefined_syms.ld; `include/actor.h` (not yet used).
- The permuter rarely helps on raw drafts (about 10 matches in some 150 near misses at 60-120 s each).
- `tools/dupsweep.py` also installs copies that differ only in instruction immediates (the masked key groups them:
  the same code with other sound / effect ids): it maps each differing immediate and rewrites that literal of the
  C when it appears once (`imm_map`, `patch_consts`); 18 more copies at once. It keeps the linker-global names of
  config/undefined_syms.ld (g_CameraState, ...) instead of renaming them to a program's D_ name, falls back to
  install_c.py for type clashes, and `-v` says why a copy was not taken.
- Library: string literals now become the retail strings' symbols, objects with extra text are rejected (+4).
- Known left-overs worth a look: f_LoadResourceChunkIntoGroup, f_ReleaseActorModelParts (lui order), func_8003F2F8, func_8003F31C, func_8004D8B0, func_8006914C (near misses written by hand, in no file yet).

## 2026-11-14: Phase 1 (Psy-Q library), partly done

- 1.1 / 1.2 done. 1.3: **314 of 867 library functions in C, 71 asm by design, ~480 left** (`python3 -I tools/progress.py`).
- Layout: the library range of MAIN and boot is one splat `c` subsegment per function (`tools/libsplit.py`),
  `src/<prog>/psyq/<lib>/<name>.c`; each file can carry `// CC`, `// FLAGS`, `// ASPSX`, `// AS gnu` (tools/cc.py);
  library files are padded to their retail size (objects end on 16 bytes). `config/aliases_<prog>.ld`: addresses of the
  names that C from other projects uses (`tools/libsweep.py` reads them off the retail code).
- Tools: `name_lib.py` (signature names), `libsweep.py --install` (candidates from psx_tomba `ptsrc.py`, Tombi-Decomp,
  m2c with typed Psy-Q context, MAIN for boot; under 8 compiler set-ups), `libnear.py` + `libpermute.py` (near misses
  + decomp-permuter), `asm_by_design.py`, `sync_src.py` (keeps main.c in step after re-splits), `t1match.py`.
- External, fetched, never committed: psx_tomba (/tmp/psx_tomba, its headers to include/pt and include/psyq), psyz
  (/opt/psyz: Psy-Q 4.0 decomp, MIT), Psy-Q 4.0/4.7 SDK headers (/opt/psyq_sdk, psyz's release assets).
- Known: some library functions match alone but not linked (CdComstr, CdIntstr, ClearImage2, SetDispMask, RotMatrix,
  RotTransPers, SetGeomScreen, PadInfoAct, _padClrIntSio0, rcos): to look at.

## 2026-11-13 (5): Phase 0 tooling, first automatic sweep

- 0.1 `tools/ccheck.py`: checks the function length too; `--func NAME`; INCLUDE_ASM functions skipped unless `--all`.
- 0.2 `tools/decomp.py NAME [--check] [--write]`: m2c draft with `include/*.h` as context (m2c in /opt/m2c).
- 0.4 `tools/sweep.py [--max-size 0x100] --install`: drafts every pending function, installs the ones that match as
  drafted (function + its `extern` lines), keeps only what leaves the linked build OK.
- Result: **41 / 1739 MAIN functions in C** (39 from the sweep). m2c drafts with no types: they will be cleaned up
  as headers grow (2.1).
- Left from the sweep: `func_8004DBB0` (extern type clash), `func_80083AF8`, `func_80086604`, `func_80092B9C`,
  `func_8009413C` (match alone, change the linked build: check rodata).
- 0.3 `tools/permute.py NAME --src FILE.c [--seconds N]` (decomp-permuter in /opt/permuter): matched
  `f_TestAppleCollectedBit` at once. First header: `include/game.h` (GameState at 0x800BF870, apple bits at +0x544).
- 0.5 deferred to Phase 5 (docs/ROADMAP.md). **42 MAIN functions in C.**
Next: Phase 1 (Psy-Q library names and C).

## 2026-11-13 (4): C in the linked build

- `config/main.yaml`: the text is a `c` subsegment, `src/main/main.c` (generated once by splat, now hand-edited:
  one `INCLUDE_ASM("asm/main/nonmatchings/main", NAME)` per function not yet in C). `include/common.h` holds
  INCLUDE_ASM (maspsx-keep) and the basic types.
- `tools/build.py` compiles `.c` with the game's pipeline (gcc 2.8.1 cc1 `-O2 -G0 -funsigned-char`, maspsx 2.79,
  as -O1); still **29 / 29 OK** with `f_StopVoicePlayback` and `f_SetIdentityMatrix` compiled from C.
- `tools/progress.py`: functions / bytes now in C per program (2 / 1739 in MAIN).

How to decompile a function: replace its INCLUDE_ASM line in `src/main/main.c` by C (declarations at the top of the
file for now), check quickly with `tools/ccheck.py src/main/main.c` (or a scratch file with just the function), then
`python3 tools/build.py main --no-split` must print OK.

Next: headers (`include/` game structs from Tomba2Edit names), split main.c into files when areas of the code are
understood, permuter, the boot exe and small overlays to `c` the same way.

## 2026-11-13 (3): reference switched to USA SCUS-94454

User's decision, because Tomba2Edit / Tomba Club work on USA addresses. `config/*.yaml` = USA (29 / 29 OK),
`config/eu/` = EU (29 / 29 OK, `tools/build.py --version eu`, asm in `asm/eu/`). Load addresses are found per version
by `tools/gen_configs.py`. Names: USA 886, EU 885; fixed a bug of the first import (names parked by Tomba2Edit on one
shared address had been taken: now dropped). Probe C still matches on USA. USA: 7037 functions, 5161 game functions,
2.31 MB (docs/PLAN.md). `tools/disc_fetch.sh` now keeps the USA image (`game/usa.img`) on a fresh download; no tool needs it yet.
Open: the 118 Tomba2Edit `FUN_*` starts that are not starts in our split (docs/TOMBA2EDIT.md).

## 2026-11-13 (2): Tomba2Edit names, compiler found

- Tomba2Edit reviewed (docs/TOMBA2EDIT.md): **899 EU functions named** (later corrected: see above) from its USA symbols and USA->EU maps
  (`tools/import_names.py`, `// t2e` lines); overlay load addresses confirmed; container formats documented.
- **Compiler: Psy-Q 4.4 = gcc 2.8.1 + ASPSX 2.79** (docs/COMPILER.md). First two functions matched in C
  (first in `src/main/ccprobe.c`, now in `src/main/main.c`; checked with `tools/ccheck.py`: compile + word compare, relocated fields masked; it does
  not yet check that the retail function has the same length).

Next:
1. C in the linked build (now on USA): switch `config/main.yaml` to a `c` subsegment layout (per-file `INCLUDE_ASM`, splat
   `asm/nonmatchings`), compile with the 2.8.1 pipeline in `tools/build.py`, keep 29/29 OK.
2. Headers: game-state struct at `D_800BFFC0`, actor struct (from Tomba2Edit's names: `f_SetActorAnimation` writes
   +0x46, +0x79, reads +0x7C), Psy-Q 4.4 headers.
3. Permuter (`tools/permute.py` from T1) for the two near-misses in docs/COMPILER.md.
4. Name the Psy-Q functions (signature hits) where Tomba2Edit has no name.

## 2026-11-13: repo bootstrap, disc survey, all-asm matching build

Done:
- Repo set up from Tombi-Decomp's tools (CLAUDE.md, README, .gitignore, `tools/session_bootstrap.sh`,
  `tools/disc_fetch.sh`, `ci_download.sh`, `disc_unpack.sh`, `isoext.py`, `setup_native.sh`, `setup_psyq.sh`,
  `psyq_cc.sh`).
- The three discs surveyed: docs/DISCS.md. ES and USA are separate builds (98 % / 96 % of EU functions found).
- Psy-Q version: **4.4** (object signatures; 245 objects / 117 KB in MAIN.EXE).
- splat configs for all 29 EU programs (`tools/gen_configs.py`: boot, MAIN, 28 overlays) and `tools/build.py`:
  **29 / 29 rebuild byte-identical** from disassembly.
- Function census (`tools/funcstats.py`): 7051 functions, 858 Psy-Q, 1019 exact dups, **5174 game functions /
  2.31 MB**. Plan: docs/PLAN.md.

Decisions (confirmed by the user 2026-11-13):
- Reference version EU SCES-02147 (changed to USA, see above).
- No decomp.dev report / report CI: progress is measured locally (tools/funcstats.py, later a local progress script).
- Layout (left to Claude): `game/<eu|es|usa>/` = the disc's files (only `game/eu.img` kept), `config/<prog>.yaml` per program,
  `asm/`, `build/` generated. Per-version configs will go to `config/<version>/` as in T1.

Next:
1. (done, see above) compiler identification.
2. Name the Psy-Q functions in `config/symbol_addrs_main.txt` / `_boot.txt` from the signature hits.
3. Find the overlay loader in MAIN.EXE (confirm 0x80109D84 / 0x80106D80 / 0x80188000).
4. Container formats (TOMBA2.IDX/DAT/IMG/SND) for the port; tools/psxemu profile for T2.

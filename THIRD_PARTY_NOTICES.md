# Third-party notices

- Function names in `config/symbol_addrs_*.txt` marked `// t2e` come from
  [Tomba2Edit](https://github.com/SiergiejW/Tomba2Edit) by SiergiejW and the
  [Tomba Club](https://tomba.club) community research it builds on (docs/TOMBA2EDIT.md).
- Psy-Q library identification uses the signatures of
  [lab313ru/psx_psyq_signatures](https://github.com/lab313ru/psx_psyq_signatures) (fetched at build time, not stored).
- Tools adapted from [Tombi-Decomp](https://github.com/afsenovilla/Tombi-Decomp) (MIT, "afsenovilla and
  Tombi-Decomp contributors"). Game C adapted from its matched C says so in a comment above the function
  (`src/main/main.c` f_AdvanceActorTimedFrameSequence, from its src/AnimAdvance.c).
- The native port (`port/`) is adapted from Tombi-Decomp's `port/` and `port2/` (MIT, same author and contributors):
  the runtime (i386 address space, MIPS interpreter, threads, GTE), the software GPU, the Psy-Q shims, the SDL2
  viewer (`port/tools/view/tomba2_view.c`, `port/runtime/window.c`), the memory card (`port/shims/card.c`), the Win32
  runtime (`port/runtime/sys_win32_i386.c`, `port/cmake/mingw-i686.cmake`), the software SPU and libsnd (`port/shims/sound.c`) and the generator design; each file says what it took (docs/PORT.md §3).
- Library C (files under `src/*/psyq/`) is adapted from these MIT-licensed decompilations of Sony's Psy-Q libraries;
  each file says where it came from (`// Source: ...`):
  [psx_tomba](https://github.com/hansbonini/psx_tomba) (MIT per its README; its base headers are fetched into
  `include/pt/` at set-up time), [psyz](https://github.com/Xeeynamo/psyz) (MIT) and
  [psy-q-decomp](https://github.com/sozud/psy-q-decomp) (MIT, "the psy-q-decomp contributors").

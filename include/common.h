#ifndef COMMON_H
#define COMMON_H

/* Shared by every C file of the decomp. INCLUDE_ASM keeps a not-yet-decompiled function as its splat assembly
 * (asm/<prog>/nonmatchings/...), passed through maspsx untouched. */

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)                                                   \
    __asm__(".text                                      # maspsx-keep\n"           \
            "\t.align\t2                                # maspsx-keep\n"           \
            "\t.set noreorder                           # maspsx-keep\n"           \
            "\t.set noat                                # maspsx-keep\n"           \
            ".include \"" FOLDER "/" #NAME ".s\"        # maspsx-keep\n"           \
            "\t.set reorder                             # maspsx-keep\n"           \
            "\t.set at                                  # maspsx-keep\n")
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)                                                \
    __asm__(".section .rodata                           # maspsx-keep\n"           \
            ".include \"" FOLDER "/" #NAME ".s\"        # maspsx-keep\n"           \
            ".text                                      # maspsx-keep\n")
#endif

__asm__(".include \"macro.inc\"                         # maspsx-keep\n");

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

#endif

/* Force-included before every generated game source of the port (port/tools/gen_t2.py). */
#ifndef PORT_PRELUDE_H
#define PORT_PRELUDE_H
#define PORT 1
/* register-carried arguments (gen_t2.py forward_short_calls): the caller's incoming argument i, i.e. what $a0-$a3
   held on entry to the caller (from Tombi-Decomp's port/include/port_prelude.h; needs -fno-omit-frame-pointer) */
#define PORT_ARG(i) (((int *)__builtin_frame_address(0))[2 + (i)])
/* the software GTE (runtime/gte.c) behind the translated inline asm (gen_t2.py translate_asm) */
void port_gte_op(unsigned long op);
void port_gte_mtc2(int reg, unsigned long v);
unsigned long port_gte_mfc2(int reg);
void port_gte_ctc2(int reg, unsigned long v);
unsigned long port_gte_cfc2(int reg);
/* a RAM pointer the game keeps in its KUSEG view (below 0x200000: the actor animation pointer at +0x38 with its
   bit-31 flag cleared, gen_t2.py kuseg_field38): the same byte through KSEG0, which is always mapped */
static __inline__ __attribute__((always_inline)) void *port_kptr(const void *p) {
    unsigned long v = (unsigned long)p;
    return (void *)(v - 0x10000ul < 0x1F0000ul ? v | 0x80000000ul : v);
}
#endif

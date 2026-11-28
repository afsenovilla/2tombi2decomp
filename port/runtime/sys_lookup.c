/* Calls to retail addresses, shared by both hosts (sys_linux_i386.c, sys_win32_i386.c): the native function for a
 * retail address (game C of MAIN or of the resident overlay, a Psy-Q shim), the MIPS interpreter otherwise, logged
 * stubs for the Psy-Q functions that touch hardware.  From Tombi-Decomp's port/runtime/sys_linux_i386.c (MIT, same
 * author), with the overlay dispatch of stage 2 (docs/PORT.md §0). */
#include "port_runtime.h"
u32p port_force_interp[8];      /* --interp ADDR: run that function in the MIPS interpreter (checks translations) */
u32p port_interp_lo, port_interp_hi;   /* --interp-range LO-HI: every game function in [LO, HI) interpreted (bisection) */
int port_ovl_native = 1;               /* --no-ovl-native: overlay code always in the interpreter (stage-1 behaviour) */
static int ovl_resident[8];            /* per load address (index of port_ovls), the overlay file read there last */
const char *port_ovl_interp[8];        /* --ovl-interp NAME: that overlay's code stays in the interpreter (bisection) */
static int ovl_disabled(int i) {
    for (int k = 0; k < 8 && port_ovl_interp[k]; k++) {
        const char *a = port_ovl_interp[k], *b = port_ovls[i].name;
        while (*a && *a == *b) { a++; b++; }
        if (!*a && !*b) return 1;
    }
    return 0;
}
static int ovl_slot(u32p vram) {
    static u32p slots[8]; static int n;
    for (int i = 0; i < n; i++) if (slots[i] == vram) return i;
    if (n < 8) { slots[n] = vram; return n++; }
    return 7;
}
void port_ovl_loaded(const char *file) {
    for (int i = 1; i < port_ovls_count; i++) {
        const char *a = port_ovls[i].file, *b = file;
        while (*a && *a == *b) { a++; b++; }
        if (!*a && !*b) { ovl_resident[ovl_slot(port_ovls[i].vram)] = i; return; }
    }
}
/* the file of the overlay read last at a load address (0: none yet), for runtime/debugmenu.c */
const char *port_ovl_resident(u32p vram) {
    int i = ovl_resident[ovl_slot(vram)];
    return i > 0 && port_ovls[i].vram == vram ? port_ovls[i].file : 0;
}
/* gen_t2.py code_hash: FNV-1a of a function's first 8 code bytes (the funcmap holds hashes, not the game's words) */
static u32p code_hash(const unsigned char *b, u32p h) { for (int i = 0; i < 8; i++) h = (h ^ b[i]) * 0x01000193u; return h; }
static const PortFunc *find_ovl(u32p a) {
    /* the entries for this address (one per overlay with C for it): the resident overlay's, if its code is in RAM;
       else none: the interpreter.  (Never another overlay's whose first words match: a common prologue made A01's
       native code run for an asm-only A03 function at the same address.) */
    int lo = 0, hi = port_funcmap_count;
    while (lo < hi) { int m = (lo + hi) / 2; if (port_funcmap[m].addr < a) lo = m + 1; else hi = m; }
    const unsigned char *ram = (const unsigned char *)a;
    u32p h0 = 0, h1 = 0;
    for (int i = lo; i < port_funcmap_count && port_funcmap[i].addr == a; i++) {
        const PortFunc *f = &port_funcmap[i];
        if (!f->ovl) continue;
        if (!h0 && !h1) { h0 = code_hash(ram, 0x811C9DC5u); h1 = code_hash(ram, 0x01000193u ^ 0x5BD1E995u); }
        if (h0 != f->w0 || h1 != f->w1) continue;
        if (ovl_resident[ovl_slot(port_ovls[f->ovl].vram)] == f->ovl) return ovl_disabled(f->ovl) ? 0 : f;
    }
    return 0;
}
const PortFunc *port_lookup_func(u32p a) {
    int lo = 0, hi = port_funcmap_count - 1;
    for (int i = 0; i < 8 && port_force_interp[i]; i++) if (port_force_interp[i] == a) return 0;
    if (a >= port_interp_lo && a < port_interp_hi) return 0;
    if (a >= PORT_OVL_BASE && a < PORT_OVL_END) return port_ovl_native ? find_ovl(a) : 0;
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        if (port_funcmap[m].addr == a) return &port_funcmap[m];
        if (port_funcmap[m].addr < a) lo = m + 1; else hi = m - 1;
    }
    return 0;
}
static void *port_lookup_1(u32p a);
void *port_lookup(u32p a) {
    extern int port_debug_hooks;                /* --debug-menu noclip / fly (runtime/debugmenu.c); 0 otherwise */
    extern void *port_debug_hook(u32p a, void *f);
    void *f = port_lookup_1(a);
    return port_debug_hooks ? port_debug_hook(a, f) : f;
}
static void *port_lookup_1(u32p a) {
    const PortFunc *f = port_lookup_func(a);
    if (f) return f->fn;
    int lo = 0, hi = port_libmap_count - 1;        /* a Psy-Q function replaced by a shim */
    for (int i = 0; i < 8 && port_force_interp[i]; i++) if (port_force_interp[i] == a) return 0;
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        if (port_libmap[m].addr == a) return port_libmap[m].fn;
        if (port_libmap[m].addr < a) lo = m + 1; else hi = m - 1;
    }
    return 0;
}
int port_lookup_ret(u32p a) { const PortFunc *f = port_lookup_func(a); return f ? f->ret : 0; }
const PortLibAddr *port_lib_info(u32p a) {
    int lo = 0, hi = port_libaddrs_count - 1;
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        if (port_libaddrs[m].addr == a) return &port_libaddrs[m];
        if (port_libaddrs[m].addr < a) lo = m + 1; else hi = m - 1;
    }
    return 0;
}
int port_is_lib_addr(u32p a) { const PortLibAddr *l = port_lib_info(a); return l && !l->pure; }

int port_stub_ret0(void) { return 0; }
#define MAX_STUBS 1024
static const char *stub_seen[MAX_STUBS];
static int stub_count[MAX_STUBS];
static int n_stub_seen;
void port_stub(const char *name, u32p addr) {
    int i;
    for (i = 0; i < n_stub_seen; i++) if (stub_seen[i] == name) break;
    if (i == n_stub_seen && n_stub_seen < MAX_STUBS) { stub_seen[n_stub_seen++] = name; }
    if (i < MAX_STUBS) stub_count[i]++;
    if (i < MAX_STUBS && (stub_count[i] == 1 || port_verbose > 1))
        port_printf("[port] stub %s (%08x) frame %d\n", name, addr, port_frame);
}
void port_stub_report(void) {
    port_printf("[port] %d calls ran in the MIPS interpreter (code without C)\n", port_mips_calls());
    port_printf("[port] %d distinct stubbed functions were called:\n", n_stub_seen);
    for (int i = 0; i < n_stub_seen; i++) port_printf("  %6d  %s\n", stub_count[i], stub_seen[i]);
}

int port_interpretable(u32p a) {
    return port_interp && a >= 0x80010000u && a < 0x80200000u && !(a & 3) && !port_is_lib_addr(a);
}
const char *port_lib_name(u32p a, const char *name) { const PortLibAddr *l = port_lib_info(a); return l ? l->name : name; }
static void *resolve_call_1(u32p addr, const char *name) {
    void *f = addr ? port_lookup(addr) : 0;
    port_last_resolve_addr = addr; port_last_resolve_name = name;
    if (f) return port_last_resolve_fn = f;
    if (port_interpretable(addr)) {            /* no C for it: run the retail machine code */
        port_mips_pending = addr;
        return port_last_resolve_fn = (void *)port_mips_entry;
    }
    port_stub(port_lib_name(addr, name ? name : "?"), addr);
    return port_last_resolve_fn = (void *)port_stub_ret0;
}
void *port_resolve_call(u32p addr, const char *name) {
    void *f = resolve_call_1(addr, name);
    port_note_resolve(addr, name, f);   /* the last 8 answers are printed by a fault report */
    return f;
}

/* SIGSEGV: execution reached a retail address (function pointer from retail data or from a table the game
   built).  The faulting EIP *is* the PS1 address; the return address and the arguments are already on the
   stack (cdecl), so redirecting EIP to the native function completes the call. */

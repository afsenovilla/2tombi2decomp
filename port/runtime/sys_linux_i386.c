/* Freestanding i386 Linux runtime for the port prototype: entry point, raw syscalls, the PS1 address space,
 * the SIGSEGV trampoline that turns calls to retail code addresses into calls to the native functions, and
 * a SIGFPE handler that gives MIPS results for division by zero.
 *
 * Why freestanding: the game's structures hold 32-bit pointers, so the port is an i386 binary, and the game's own
 * libc names (memcpy, strlen, printf, open, read ...) must not meet a host libc.  From Tombi-Decomp's port/ (MIT,
 * same author), adapted: one lookup table (no overlay C yet), the Psy-Q address policy of gen_t2.py. */
#include "port_runtime.h"

#define SYS_exit_group 252
#define SYS_read 3
#define SYS_write 4
#define SYS_open 5
#define SYS_close 6
#define SYS_lseek 19
#define SYS_mmap2 192
#define SYS_rt_sigaction 174
#define SYS_rt_sigreturn 173
#define SYS_nanosleep 162
#define SYS_clock_nanosleep 267
#define SYS_clock_gettime 265
#define SYS_llseek 140
#define SYS_pread64 180

static long sys3(long n, long a, long b, long c) {
    long r;
    __asm__ volatile("int $0x80" : "=a"(r) : "a"(n), "b"(a), "c"(b), "d"(c) : "memory");
    return r;
}
static long sys5(long n, long a, long b, long c, long d, long e) {
    long r;
    __asm__ volatile("int $0x80" : "=a"(r) : "a"(n), "b"(a), "c"(b), "d"(c), "S"(d), "D"(e) : "memory");
    return r;
}
static long sys6(long n, long a, long b, long c, long d, long e, long f) {
    long r;
    /* ebp carries the 6th argument */
    __asm__ volatile("push %%ebp\n\tmov %7, %%ebp\n\tint $0x80\n\tpop %%ebp"
                     : "=a"(r) : "a"(n), "b"(a), "c"(b), "d"(c), "S"(d), "D"(e), "g"(f) : "memory");
    return r;
}

void port_exit(int code) { for (;;) sys3(SYS_exit_group, code, 0, 0); }

static int slen(const char *s) { int n = 0; while (s[n]) n++; return n; }
void port_puts(const char *s) { sys3(SYS_write, 2, (long)s, slen(s)); }

/* ------------------------------------------------------------------------------------------- files, time */
int port_open(const char *p) { long r = sys3(SYS_open, (long)p, 0 /* O_RDONLY */, 0); return r < 0 ? -1 : (int)r; }
int port_read(int fd, void *b, int n) { return (int)sys3(SYS_read, fd, (long)b, n); }
int port_create(const char *p) { long r = sys3(SYS_open, (long)p, 0x241 /* O_WRONLY|O_CREAT|O_TRUNC */, 0644); return r < 0 ? -1 : (int)r; }
/* a pipe for a player: O_RDWR on a FIFO never blocks in open() (so players that open their inputs one after the
   other cannot deadlock against us); a regular file is created / truncated */
int port_open_pipe(const char *p) {
    long r = sys3(SYS_open, (long)p, 0x242 /* O_RDWR|O_CREAT|O_TRUNC */, 0644);
    if (r >= 0) sys3(55 /* fcntl */, r, 1031 /* F_SETPIPE_SZ */, 1 << 20);   /* a FIFO: 1 MB of slack (fails harmlessly on files) */
    return r < 0 ? -1 : (int)r;
}
int port_write(int fd, const void *b, int n) { return (int)sys3(SYS_write, fd, (long)b, n); }
/* --window: pipes to a viewer process.  port_spawn runs PATH with ARGV; its stdin is the read end of a pipe we
   write (fd 0 in the child), ARGV may name more fds.  fds[0] = our write end for the child's stdin (video),
   fds[1] = our write end for the child's fd 3 (audio), fds[2] = our read end of the child's fd 4 (pad), made
   non-blocking.  Returns the child's pid or -1. */
extern char **port_envp;
int port_spawn(const char *path, char *const argv[], int fds[3]) {
    int v[2], a[2], p[2];
    if (sys3(42 /* pipe */, (long)v, 0, 0) < 0 || sys3(42, (long)a, 0, 0) < 0 || sys3(42, (long)p, 0, 0) < 0) return -1;
    long pid = sys3(2 /* fork */, 0, 0, 0);
    if (pid < 0) return -1;
    if (pid == 0) {
        /* our ends first (they are not 0/3/4: the pipe fds are all above the disc image's fd) */
        sys3(SYS_close, v[1], 0, 0); sys3(SYS_close, a[1], 0, 0); sys3(SYS_close, p[0], 0, 0);
        sys3(63 /* dup2 */, v[0], 0, 0); sys3(63, a[0], 3, 0); sys3(63, p[1], 4, 0);
        int orig[3] = { v[0], a[0], p[1] };
        for (int i = 0; i < 3; i++) if (orig[i] > 4) sys3(SYS_close, orig[i], 0, 0);
        sys3(11 /* execve */, (long)path, (long)argv, (long)port_envp);
        port_puts("[port] cannot exec the viewer\n");
        sys3(SYS_exit_group, 127, 0, 0);
    }
    sys3(SYS_close, v[0], 0, 0); sys3(SYS_close, a[0], 0, 0); sys3(SYS_close, p[1], 0, 0);
    sys3(55 /* fcntl */, v[1], 1031 /* F_SETPIPE_SZ */, 1 << 20);
    sys3(55, a[1], 1031, 1 << 20);
    sys3(55, p[0], 4 /* F_SETFL */, 04000 /* O_NONBLOCK */);
    fds[0] = v[1]; fds[1] = a[1]; fds[2] = p[0];
    return (int)pid;
}
int port_write_all(int fd, const void *b, int n) {   /* a pipe write may be short when a signal arrives */
    const char *c = b; int left = n;
    while (left > 0) {
        long r = sys3(SYS_write, fd, (long)c, left);
        if (r == -4 /* EINTR */) continue;
        if (r <= 0) return n - left;
        c += r; left -= r;
    }
    return n;
}
int port_mkdir(const char *p) { return (int)sys3(39 /* SYS_mkdir */, (long)p, 0755, 0); }
void port_close(int fd) { sys3(SYS_close, fd, 0, 0); }
int port_pwrite(int fd, const void *b, int n, long long off) {
    return (int)sys5(181 /* SYS_pwrite64 */, fd, (long)b, n, (long)(unsigned)off, (long)(off >> 32));
}
static int last_error;
int port_last_error(void) { return last_error; }
int port_pread(int fd, void *b, int n, long long off) {
    int r = (int)sys5(SYS_pread64, fd, (long)b, n, (long)(unsigned)off, (long)(off >> 32));
    if (r < 0) { last_error = -r; return -1; }
    last_error = 0;
    return r;
}
long long port_filesize(int fd) {
    long long res = 0;
    sys5(SYS_llseek, fd, 0, 0, (long)&res, 2 /* SEEK_END */);
    return res;
}
struct ts { long s, ns; };
unsigned long long port_time_us(void) {
    struct ts t; sys3(SYS_clock_gettime, 1 /* MONOTONIC */, (long)&t, 0);
    return (unsigned long long)t.s * 1000000ull + t.ns / 1000;
}
void port_sleep_us(unsigned long long us) {
    struct ts t = { (long)(us / 1000000ull), (long)(us % 1000000ull) * 1000 };
    sys3(SYS_nanosleep, (long)&t, 0, 0);
}
/* sleep until an absolute CLOCK_MONOTONIC time (TIMER_ABSTIME: no error accumulates across frames), the last
   ~200 us spun */
void port_sleep_until_us(unsigned long long deadline) {
    unsigned long long now = port_time_us();
    if (deadline > now + 300) {
        unsigned long long d = deadline - 200;
        struct ts t = { (long)(d / 1000000ull), (long)(d % 1000000ull) * 1000 };
        sys5(SYS_clock_nanosleep, 1 /* MONOTONIC */, 1 /* TIMER_ABSTIME */, (long)&t, 0, 0);
    }
    while (port_time_us() < deadline) ;
}

static void *map_fixed(unsigned addr, unsigned size) {
    /* PROT_READ|PROT_WRITE (no exec: a call into it faults and is resolved below),
       MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED_NOREPLACE */
    long r = sys6(SYS_mmap2, addr, size, 3, 0x02 | 0x20 | 0x100000, -1, 0);
    if ((unsigned long)r != addr) port_fatal("cannot map PS1 memory at %08x (got %lx)", addr, r);
    return (void *)r;
}

/* ------------------------------------------------------------------------------------------- calls to retail addresses */
/* (the lookup tables, stubs and the interpreter fallback are in sys_lookup.c) */
struct ksigaction { void *handler; unsigned long flags; void *restorer; unsigned long mask[2]; };
extern void port_sigreturn(void);
__asm__(".text\n.globl port_sigreturn\nport_sigreturn:\n\tmovl $173, %eax\n\tint $0x80\n");

#define UC_EIP(uc) (((unsigned long *)(uc))[5 + 14])
#define UC_ESP(uc) (((unsigned long *)(uc))[5 + 7])
#define UC_EAX(uc) (((unsigned long *)(uc))[5 + 11])
#define UC_EDX(uc) (((unsigned long *)(uc))[5 + 9])
#define UC_CR2(uc) (((unsigned long *)(uc))[5 + 21])
#define UC_EDI(uc) (((unsigned long *)(uc))[5 + 4])
#define UC_ESI(uc) (((unsigned long *)(uc))[5 + 5])
static unsigned char *low_scratch;   /* executable page for port_low_emulate (port_setup_memory) */

static void on_segv(int sig, void *info, void *uc) {
    unsigned long eip = UC_EIP(uc);
    unsigned long fault = ((unsigned long *)info)[3];
    if (eip == fault && (eip & 0x5FFFFFFFul) < 0x00200000ul) {   /* KUSEG / KSEG0 / KSEG1 RAM address */
        void *f = port_lookup((u32p)(0x80000000ul | (eip & 0x1FFFFFul)));
        if (f) { UC_EIP(uc) = (unsigned long)f; return; }
        if (port_interpretable((u32p)(0x80000000ul | (eip & 0x1FFFFFul)))) {
            port_mips_pending = (u32p)(0x80000000ul | (eip & 0x1FFFFFul));
            UC_EIP(uc) = (unsigned long)port_mips_entry;
            return;
        }
        port_stub(port_lib_name(0x80000000u | (eip & 0x1FFFFFu), "<retail address without native code>"), (u32p)eip);
        UC_EIP(uc) = (unsigned long)port_stub_ret0;
        return;
    }
    if (eip != fault && fault < 0x00200000ul && low_scratch) {   /* page 0 or an unmapped KUSEG mirror (--no-kuseg) */
        unsigned long neweip;
        int r = port_low_emulate(eip, fault, low_scratch, &neweip);
        if (r == PORT_LOW_JUMP) { UC_EIP(uc) = neweip; return; }
        if (r == PORT_LOW_REGS) {
            if (UC_ESI(uc) < 0x00200000ul) UC_ESI(uc) |= 0x80000000ul;
            if (UC_EDI(uc) < 0x00200000ul) UC_EDI(uc) |= 0x80000000ul;
            return;
        }
    }
    unsigned long ret = *(unsigned long *)UC_ESP(uc);
    {   /* stack scan: words that look like native return addresses, with the nearest native function
           (sys_common.c port_dump_stack; exact lines: addr2line -f -e tombi) */
        extern char __executable_start[], etext[];
        port_printf("[port] eax=%08lx edx=%08lx; stack:", UC_EAX(uc), UC_EDX(uc));
        port_dump_stack((const unsigned long *)UC_ESP(uc), (unsigned long)__executable_start, (unsigned long)etext);
    }
    port_low_report();   /* emulated low accesses so far: a partial KUSEG mirror in use shows here */
    port_fatal("signal %d: eip=%08lx fault address=%08lx (frame %d, [esp]=%08lx)", sig, eip, fault, port_frame, ret);
}

/* SIGFPE (x86 traps on division by zero, the R3000 does not): emulate LO = rs < 0 ? 1 : -1, HI = rs */
static void on_fpe(int sig, void *info, void *uc) {
    unsigned char *p = (unsigned char *)UC_EIP(uc);
    int len = 0;
    if (p[0] == 0xF7) {
        unsigned char modrm = p[1]; int mod = modrm >> 6, rm = modrm & 7;
        len = 2;
        if (mod != 3 && rm == 4) len++;                         /* SIB */
        if (mod == 1) len += 1; else if (mod == 2) len += 4;
        else if (mod == 0 && rm == 5) len += 4;
        else if (mod == 0 && rm == 4 && (p[2] & 7) == 5) len += 4;
    }
    if (!len) port_fatal("SIGFPE at %08lx", UC_EIP(uc));
    long rs = (long)UC_EAX(uc);
    UC_EDX(uc) = (unsigned long)rs;
    UC_EAX(uc) = rs < 0 ? 1 : (unsigned long)-1;
    UC_EIP(uc) += len;
    (void)sig; (void)info;
}

/* SIGALRM every 2 s (wall clock): a run whose frame counter stopped (a busy loop the vblank heuristics do not
   catch, e.g. polling a shim) reports where it is: native EIP, the interpreter's pc, the last call thunk; after
   20 s without a frame it stops. */
static int alarm_last_frame = -1, alarm_stalls;
static void on_alarm(int sig, void *info, void *uc) {
    (void)sig; (void)info;
    if (port_frame != alarm_last_frame) { alarm_last_frame = port_frame; alarm_stalls = 0; return; }
    alarm_stalls++;
    unsigned long off; const char *nm = port_sym_near(UC_EIP(uc), &off);
    extern u32p port_mips_cur_pc, port_mips_cur_entry;
    port_printf("[port] watchdog: no vblank for %d s (frame %d): eip %08lx (%s+0x%lx), interpreter pc %08x (function %08x), "
                "last call thunk %s (%08x)\n", alarm_stalls * 2, port_frame, UC_EIP(uc), nm ? nm : "?", nm ? off : 0,
                port_mips_cur_pc, port_mips_cur_entry, port_last_resolve_name ? port_last_resolve_name : "-", port_last_resolve_addr);
    if (alarm_stalls >= 10) { extern void port_stub_report(void); port_stub_report(); port_fatal("watchdog: the game stopped advancing"); }
}

static void install(int sig, void *h) {
    struct ksigaction sa = { h, 4 /* SA_SIGINFO */ | 0x04000000 /* SA_RESTORER */ | 0x40000000 /* SA_NODEFER */,
                             (void *)port_sigreturn, { 0, 0 } };
    sys5(SYS_rt_sigaction, sig, (long)&sa, 0, 8, 0);
}

/* ------------------------------------------------------------------------------------------- entry */
int port_verbose, port_kuseg_strict;
char **port_envp;
extern int port_main(int argc, char **argv);

static void map_shared(int fd, unsigned addr, unsigned size, unsigned off) {
    long r = sys6(SYS_mmap2, addr, size, 3, 0x01 /* MAP_SHARED */ | 0x100000, fd, off >> 12);
    if ((unsigned long)r != addr) port_fatal("cannot map PS1 RAM mirror at %08x (got %lx)", addr, r);
}

int port_low_mem = -1;          /* lowest mapped address of the KUSEG kernel area (0 or 0x1000), -1: none */
void port_setup_memory(void) {
    /* One 2 MB RAM object seen at KSEG0 0x80000000 (what the game uses), KUSEG 0x00000000 (the game masks
       addresses with 0xFFFFFF, e.g. compactOrderingTable) and KSEG1 0xA0000000.  The first 64 KB of KUSEG
       (BIOS kernel area) is mapped as far as vm.mmap_min_addr allows: game code reads it through NULL pointers
       (WMD_DATA of a room without a model, an animation pointer before it is set) and sees the zeroed kernel
       area of the RAM object, as on a PS1.  Page 0 needs vm.mmap_min_addr = 0. */
    long fd = sys3(356 /* memfd_create */, (long)"psx-ram", 0, 0);
    if (fd < 0) port_fatal("memfd_create failed (%ld)", fd);
    sys3(93 /* ftruncate */, fd, PSX_RAM_SIZE, 0);
    map_shared((int)fd, PSX_RAM_BASE, PSX_RAM_SIZE, 0);
    if (port_kuseg_strict == 2)   /* --no-kuseg: no mirror, every masked access faults into port_low_emulate and is tallied */
        port_printf("[port] --no-kuseg: the KUSEG mirror 0x10000-0x1FFFFF is not mapped; accesses there are emulated and counted\n");
    else
        map_shared((int)fd, 0x00010000u, PSX_RAM_SIZE - 0x10000u, 0x10000u);
    low_scratch = (unsigned char *)sys6(SYS_mmap2, 0, 0x1000, 7 /* RWX */, 0x22 /* MAP_PRIVATE|MAP_ANONYMOUS */, -1, 0);
    if ((unsigned long)low_scratch > 0xFFFFF000ul) port_fatal("cannot map the instruction scratch page");
    {
        long r = sys6(SYS_mmap2, 0, 0x10000u, 3, 0x01 | 0x100000, fd, 0);
        if (r != 0) r = sys6(SYS_mmap2, 0x1000u, 0xF000u, 3, 0x01 | 0x100000, fd, 1);
        port_low_mem = r == 0 ? 0 : (unsigned long)r == 0x1000u ? 0x1000 : -1;
    }
    map_shared((int)fd, 0xA0000000u, PSX_RAM_SIZE, 0);
    map_fixed(PSX_SPAD_BASE, PSX_SPAD_SIZE);
    install(11, (void *)on_segv);   /* SIGSEGV */
    install(8, (void *)on_fpe);     /* SIGFPE */
    install(7, (void *)on_segv);    /* SIGBUS */
    install(14, (void *)on_alarm);  /* SIGALRM: the watchdog */
    {   /* setitimer(ITIMER_REAL, 2 s) */
        long it[4] = { 2, 0, 2, 0 };
        sys3(104 /* SYS_setitimer */, 0, (long)it, 0);
    }
    {   /* SIGPIPE ignored: a video/audio pipe whose player quit reports EPIPE instead of killing the game */
        struct ksigaction sa = { (void *)1 /* SIG_IGN */, 0x04000000, (void *)port_sigreturn, { 0, 0 } };
        sys5(SYS_rt_sigaction, 13, (long)&sa, 0, 8, 0);
    }
}

__attribute__((used, noreturn)) static void cstart(unsigned long *sp) {
    int argc = (int)sp[0];
    char **argv = (char **)(sp + 1);
    port_envp = argv + argc + 1;
    port_exit(port_main(argc, argv));
}
__asm__(".text\n.globl _start\n_start:\n\txorl %ebp, %ebp\n\tmovl %esp, %eax\n\tandl $-16, %esp\n"
        "\tsubl $12, %esp\n\tpushl %eax\n\tcall cstart\n\thlt\n");

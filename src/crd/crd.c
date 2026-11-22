#include "common.h"
#include "game.h"
#include "m2c.h"

typedef struct {
    u8 x0;
    u8 x1;
    u8 x2;
    u8 x3;
    s32 x4;
    void *x8;
    void *xC;
    u8 *x10;
    u8 *x14;
    s16 x18;
    s16 x1A;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
    s32 x38;
    u8 x3C;
    u8 x3D;
    u8 x3E;
    u8 x3F;
    u8 x40;
    u8 x41;
    u8 x42;
    u8 x43;
    u8 x44;
    u8 x45;
    u8 x46;
    u8 x47;
    u8 x48[2];
    u8 x4A[2];
    u8 x4C[2];
    u8 x4E[2];
    u8 x50;
    u8 x51;
    u8 sel;
    u8 x53;
    s16 x54;
    s16 x56;
    s16 x58;
    u8 x5A;
    u8 x5B;
} CrdMenu;
extern CrdMenu D_800BF498;
/* The message-box refresh every menu step does: show message `id` (text msg) unless it is up already */
#define CRD_MSG(id, msg)                     \
    {                                        \
        CrdMenu *s;                          \
        s32 w, m;                            \
        w = id;                              \
        s = &D_800BF498;                     \
        m = -1;                              \
        if (s->x18 != w) {                   \
            func_8009A5B0(s->xC, msg);       \
            s->x18 = w;                      \
        }                                    \
        if (s->x1A != m) {                   \
            *s->x10 = 0;                     \
            s->x1A = m;                      \
        }                                    \
    }
/* The same for the second message line (x10 / x1A), clearing the first */
#define CRD_MSG2(id, msg)                    \
    {                                        \
        CrdMenu *s;                          \
        s32 w, m;                            \
        m = -1;                              \
        s = &D_800BF498;                     \
        w = id;                              \
        if (s->x18 != m) {                   \
            *(u8 *)s->xC = 0;                \
            s->x18 = m;                      \
        }                                    \
        if (s->x1A != w) {                   \
            func_8009A5B0(s->x10, msg);      \
            s->x1A = w;                      \
        }                                    \
    }
/* Which of the four card events (D_800BF498.x1C..x28) fired, 1..4, or 0 */
static inline u8 crd_card_event(void)
{
    if (func_80080840(D_800BF498.x1C) == 1) {
        return 1;
    }
    if (func_80080840(D_800BF498.x20) == 1) {
        return 2;
    }
    if (func_80080840(D_800BF498.x24) == 1) {
        return 3;
    }
    if (func_80080840(D_800BF498.x28) == 1) {
        return 4;
    }
    return 0;
}
/* crd_card_event, or 2 once the wait counter x43 runs out */
static inline u8 crd_card_event_wait(void)
{
    if (func_80080840(D_800BF498.x1C) == 1) {
        return 1;
    }
    if (func_80080840(D_800BF498.x20) == 1) {
        return 2;
    }
    if (func_80080840(D_800BF498.x24) == 1) {
        return 3;
    }
    if (func_80080840(D_800BF498.x28) == 1) {
        return 4;
    }
    if (++D_800BF498.x43 >= 0xFF) {
        return 2;
    }
    return 0;
}
typedef struct { s16 x; s16 y; u16 w; s16 h; } CrdRect;
/* One menu label: text at the right edge of the rect, then the rect widened to the text and filled (highlighted when
 * sel) */
static inline void crd_draw_label(u8 *str, CrdRect *r, s32 sel)
{
    s32 col, mode;
    if (sel) {
        col = 0;
        mode = 0x40;
    } else {
        col = 6;
        mode = 0x60;
    }
    func_80079374((s16)(r->x + r->w), r->y, col, str, 3);
    r->w *= 2;
    r->w += func_8009A600(str) << 3;
    func_8005019C(r, mode, 0, 3);
}

extern u16 D_800ECF54;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

u8 func_8018A1E8(CrdMenu *a)
{
    s32 port = a->x3D << 4;
    s32 one = 1;
    u8 r;
    switch (a->x40) {
    case 0:
        func_8009BA90(port);
        a->x40 = one;
        a->x43 = 0;
        a->x41 = 0xFF;
        break;
    case 1:
        r = crd_card_event_wait();
        if (r == 0) {
            break;
        }
        switch (r) {
        case 4:
            if (((u8 *)a + a->x3D)[0x4A] == 0) {
                a->x42 = 0;
                break;
            }
            func_80080840(D_800BF498.x2C);
            func_80080840(D_800BF498.x30);
            func_80080840(D_800BF498.x34);
            func_80080840(D_800BF498.x38);
            func_8009BAB0(port);
            while (1) {
                if (func_80080840(D_800BF498.x2C) == 1) {
                    break;
                }
                if (func_80080840(D_800BF498.x30) == 1) {
                    break;
                }
                if (func_80080840(D_800BF498.x34) == 1) {
                    break;
                }
                if (func_80080840(D_800BF498.x38) == 1) {
                    break;
                }
            }
            a->x42 = 1;
            ((u8 *)a + a->x3D)[0x48] = 0;
            ((u8 *)a + a->x3D)[0x4E] = 0xFF;
            break;
        case 1:
            a->x42 = 0;
            break;
        case 2 ... 3:
            a->x42 = 0xFE;
            ((u8 *)a + a->x3D)[0x48] = 0;
            ((u8 *)a + a->x3D)[0x4E] = 0xFF;
            break;
        }
        a->x41 = a->x42;
        ((u8 *)a + a->x3D)[0x4A] = a->x41;
        a->x40 = 0;
        a->x3D = 1 - a->x3D;
        break;
    case 2:
        break;
    }
    return a->x41;
}

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018A428);

extern u16 D_800ECF54;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern char D_8018A090[];
extern char D_8018A0A0[];
s32 func_8018AEB8(u8 *buf, s32 port, u8 *st)
{
    char name[0x20];
    s32 fd, i;
    u8 sum;
    u8 *p;
    u8 slot;
    port &= 0xFF;
    if (port == 0xFF || st[0] >= 0xF) {
        return 0;
    }
    slot = port << 4;
    func_8009B0C0(name, D_8018A090, slot, D_8018A0A0, st[0]);
    if (st[2] == 0) {
        fd = func_800808B0(name, 0x10200);
        D_800BF498.x4 = fd;
        if (fd == -1) {
            goto fail;
        }
        func_800808F0(fd);
        st[2] = 1;
        return 2;
    }
    buf[0x97E] = 3;
    p = buf + 0x380;
    sum = 0;
    for (i = 0; i < 0x5FF; i++) {
        sum ^= *p++;
    }
    buf[0x97F] = sum;
    D_800BF498.x4 = func_800808B0(name, 0x8002);
    if (D_800BF498.x4 == -1) {
        goto fail;
    }
    func_80080840(D_800BF498.x1C);
    func_80080840(D_800BF498.x20);
    func_80080840(D_800BF498.x24);
    func_80080840(D_800BF498.x28);
    func_800808E0(D_800BF498.x4, buf, 0x980);
    return 1;
fail:
    func_800808F0(D_800BF498.x4);
    return 0;
}

void func_8018B020(CrdMenu *a)
{
    char name[0x20];
    s32 ok;
    s32 i;
    u8 *dst;
    u8 *e;
    s32 k;
    char *n;
    ok = 0;
    if (a->x51++ < 7) {
        return;
    }
    e = a->x8;
    if (a->x46 != 0xFF) {
        k = a->x47 * 0x3C;
        func_8009B0C0(name, D_8018A090, a->x46 << 4, D_8018A0A0, (e + k)[4]);
        n = name;
        dst = a->x14;
        for (i = 0; i < 7; i++) {
            a->x4 = func_800808B0(n, 0x8001);
            if (a->x4 != -1) {
                if (func_800808C0(a->x4, 0x380, 0) != -1) {
                    func_80080840(D_800BF498.x1C);
                    func_80080840(D_800BF498.x20);
                    func_80080840(D_800BF498.x24);
                    func_80080840(D_800BF498.x28);
                    func_800808D0(a->x4, dst, 0x600);
                    ok = 1;
                    goto done;
                }
                func_800808F0(a->x4);
            }
        }
        ok = 0;
    }
done:
    if (ok == 0) {
        func_8001CBA8(a, a->x46);
        a->x3E = 2;
        a->x3F = 0;
        a->x40 = 0;
        return;
    }
    a->x2 = 0;
    a->x3F = 3;
}

typedef struct { u8 b[0x5F4]; } CrdSaveBlk;
extern u8 D_1F8001FF;
extern u16 D_1F800278;
void func_8018B1A4(CrdMenu *a)
{
    u8 *p, *b;
    s32 i;
    u8 sum;
    u8 port;
    s32 ff;
    a->x3E = crd_card_event();
    if (a->x3E == 0) {
        return;
    }
    func_800808F0(a->x4);
    if (a->x3E == 1 && (p = a->x14)[0x5FE] == 3) {
        b = p;
        sum = 0;
        for (i = 0; i < 0x5FF; i++) {
            sum ^= *p++;
        }
        if (b[0x5FF] == sum) {
            D_1F8001FF = D_800BF870.unk0;
            D_1F800278 = *(u16 *)((u8 *)&D_800BF870 + 0x5E6);
            *(CrdSaveBlk *)&D_800BF870 = *(CrdSaveBlk *)a->x14;
            a->x3F = 0;
            a->x40 = 0;
            return;
        }
    }
    ff = 0xFF;
    port = ff;
    if (a->x46 != ff) {
        port = a->x46 << 4;
    }
    if (a->x3E == 4 && port != ff) {
        func_80080840(D_800BF498.x2C);
        func_80080840(D_800BF498.x30);
        func_80080840(D_800BF498.x34);
        func_80080840(D_800BF498.x38);
        func_8009BAB0(port);
        while (1) {
            if (func_80080840(D_800BF498.x2C) == 1) {
                break;
            }
            if (func_80080840(D_800BF498.x30) == 1) {
                break;
            }
            if (func_80080840(D_800BF498.x34) == 1) {
                break;
            }
            if (func_80080840(D_800BF498.x38) == 1) {
                break;
            }
        }
    } else {
        a->x5A = 0x32;
    }
    if (++a->x5A < 0x33) {
        a->x3E = 0;
        a->x51 = 0;
        a->x2 = 0;
        a->x3F = 2;
        return;
    }
    a->x3E = 2;
    a->x3F = 0;
    a->x40 = 0;
}

void func_8018B478(CrdMenu *a)
{
    u8 *e;
    if (a->x51++ < 7) {
        return;
    }
    e = a->x8;
    func_8009A420(a->x14, 0, 0x980);
    func_8018A428(a->x14);
    D_800BF870.pad1[0x17A] = 0;
    *(CrdSaveBlk *)(a->x14 + 0x380) = *(CrdSaveBlk *)&D_800BF870;
    switch (func_8018AEB8(a->x14, a->x46, e + (a->x47 * 0x3C + 4))) {
    case 0:
        if (a->x46 == 0xFF || ++a->x5A >= 3) {
            func_8001CBA8(a, a->x46);
            a->x3E = 2;
            a->x3F = 0;
            a->x40 = 0;
            break;
        }
        a->x51 = 0;
        a->x2 = 0;
        break;
    case 1:
        a->x2 = 0;
        a->x3F = 6;
        break;
    case 2:
        a->x5A = 0;
        a->x51 = 0;
        a->x2 = 0;
        break;
    }
}

void func_8018B660(CrdMenu *a)
{
    char name[0x20];
    s32 ok;
    s32 i;
    u8 *dst;
    u8 *e;
    s32 k;
    char *n;
    ok = 0;
    if (a->x51++ < 7) {
        return;
    }
    e = a->x8;
    if (a->x46 != 0xFF) {
        k = a->x47 * 0x3C;
        func_8009B0C0(name, D_8018A090, a->x46 << 4, D_8018A0A0, (e + k)[4]);
        n = name;
        dst = a->x14;
        for (i = 0; i < 7; i++) {
            a->x4 = func_800808B0(n, 0x8001);
            if (a->x4 != -1) {
                if (func_800808C0(a->x4, 0x380, 0) != -1) {
                    func_80080840(D_800BF498.x1C);
                    func_80080840(D_800BF498.x20);
                    func_80080840(D_800BF498.x24);
                    func_80080840(D_800BF498.x28);
                    func_800808D0(a->x4, dst, 0x600);
                    ok = 1;
                    goto done;
                }
                func_800808F0(a->x4);
            }
        }
        ok = 0;
    }
done:
    if (ok == 0) {
        func_8001CBA8(a, a->x46);
        a->x3E = 2;
        a->x3F = 0;
        a->x40 = 0;
        return;
    }
    a->x2 = 0;
    a->x3F = 9;
}

void func_8018B7E4(CrdMenu *a)
{
    char name[0x20];
    u8 *e, *p, *b;
    s32 i, k;
    u8 sum;
    u8 port;
    u8 t;
    a->x3E = crd_card_event();
    if (a->x3E == 0) {
        return;
    }
    e = a->x8;
    func_800808F0(a->x4);
    if (a->x3E == 1 && (p = a->x14)[0x5FE] == 3) {
        b = p;
        sum = 0;
        for (i = 0; i < 0x5FF; i++) {
            sum ^= *p++;
        }
        if (b[0x5FF] == sum) {
            goto done;
        }
    }
    port = 0xFF;
    if (a->x46 != 0xFF) {
        port = a->x46 << 4;
    }
    if (port == 0xFF) {
        a->x3E = 2;
        goto done;
    }
    t = a->x5B;
    if ((t & 0xF) == a->x3E) {
        a->x5B = t + 0x10;
    } else {
        a->x5B = a->x3E;
    }
    if (a->x3E == 4) {
        func_80080840(D_800BF498.x2C);
        func_80080840(D_800BF498.x30);
        func_80080840(D_800BF498.x34);
        func_80080840(D_800BF498.x38);
        func_8009BAB0(port);
        while (1) {
            if (func_80080840(D_800BF498.x2C) == 1) {
                break;
            }
            if (func_80080840(D_800BF498.x30) == 1) {
                break;
            }
            if (func_80080840(D_800BF498.x34) == 1) {
                break;
            }
            if (func_80080840(D_800BF498.x38) == 1) {
                break;
            }
        }
        a->x5B &= 0xF;
    }
    if (port == 0xFF) {
        goto two;
    }
    if ((a->x5B & 0xF0) < 0x20) {
        goto small;
    }
    k = a->x47 * 0x3C;
    func_8009B0C0(name, D_8018A090, port, D_8018A0A0, (e + k)[4]);
    func_80080910(name);
two:
    a->x3E = 2;
    goto done;
small:
    a->x3E = 0;
    a->x51 = 0;
    a->x2 = 0;
    a->x3F = 5;
    return;
done:
    a->x3F = 0;
    a->x40 = 0;
}

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018BA68);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018BF74);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018C4B4);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018C790);

extern u8 *D_800A2854[];
void func_8018CCCC(u8 *a)
{
    s16 ids[2] = { 0x2E, 0x2F };
    CrdRect r;
    s32 i, col, mode;
    u8 *str;
    if (*(u8 *)D_800BF498.xC != 0) {
        return;
    }
    r.h = 0x10;
    r.w = 0;
    r.y = 0x64;
    for (i = 0; i < 2; i++) {
        if ((a + i)[0x4A] >= 3) {
            continue;
        }
        str = D_800A2854[ids[i]];
        r.x = 0x50 - func_8009A600(str) * 4;
        if (i != 0) {
            r.x += 0xA0;
        }
        r.y = 0x64;
        r.w = 0;
        if (a[0x44] == i + 1) {
            col = 0;
            mode = 0x40;
        } else {
            col = 6;
            mode = 0x60;
        }
        func_80079374((s16)(r.x + r.w), r.y, col, str, 3);
        r.w *= 2;
        r.w += func_8009A600(str) << 3;
        func_8005019C(&r, mode, 0, 3);
    }
}

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018CE40);

extern u8 D_8018A114[];
static inline void crd_measure(u8 *s, s32 *w, s32 *n)
{
    s32 c = 0;
    *n = 1;
    *w = 0;
    while (*s != 0) {
        if (*s == '\n') {
            if (*w < c) {
                *w = c;
            }
            c = 0;
            (*n)++;
        } else {
            c++;
        }
        s++;
    }
    if (*w < c) {
        *w = c;
    }
}

void func_8018D26C(CrdMenu *unused)
{
    CrdRect r;
    s32 w, n, y;
    u8 *s;
    if (*D_800BF498.x10 != 0) {
        func_80079374(0x64, 8, 0, D_800BF498.x10, 4);
        func_8005019C(D_8018A114, 0x40, 0, 4);
    }
    s = D_800BF498.xC;
    if (*s != 0) {
        crd_measure(s, &w, &n);
        r.x = 0xA0 - w * 4;
        r.w = w * 8;
        r.h = n * 16;
        switch (D_800BF498.x18) {
        case 0x39:
        case 0x3A:
        case 0x40:
            y = 0x8C;
            y -= n * 8;
            r.y = y;
            break;
        default:
            r.y = 0x52;
            break;
        }
        func_80079374(r.x, r.y, 0, D_800BF498.xC, 4);
        func_8005019C(&r, 0x40, 0, 4);
    }
}

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018D418);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018D74C);

void func_8018DB28(u8 *a)
{
    s16 *n = *(s16 **)(a + 8);
    if (D_800BF498.x56 != 0) {
        return;
    }
    if ((D_800ECF54 & 0x10) && a[0x47] != 0) {
        func_80074590(0x15, 0, 0);
        D_800BF498.sel = a[0x47] - 1;
        D_800BF498.x56 = 0x20;
        D_800BF498.x54 = 0x50;
        D_800BF498.x58 = 0;
    }
    if (D_800BF498.x56 == 0 && (D_800ECF54 & 0x40) && a[0x47] < *n - 1) {
        func_80074590(0x15, 0, 0);
        D_800BF498.sel = a[0x47];
        D_800BF498.x56 = 0x50;
        D_800BF498.x54 = 0x20;
        D_800BF498.x58 = 0;
    }
}

extern u16 D_800E7E68;
extern u8 *D_1F800138;
void func_8018DC2C(u8 *a)
{
    u16 k;

    switch (a[1]) {
    case 0:
        a[0x50] = 0;
        a[1]++;
        break;
    case 1:
        if (++a[0x50] >= 11) {
            a[1]++;
        }
        break;
    case 2:
        if (a[0x4A] != 0xFC && a[0x4A] != 1 && a[0x4B] != 0xFC && a[0x4B] != 1) {
            a[2] = 0;
            a[1] = 0;
            a[0] = 1;
        }
        break;
    }
    k = D_800E7E68;
    if (k & 0x2000) {
        if (!(a[0x3C] & 1)) {
            *(s16 *)(D_1F800138 + 0x50) = 2;
            return;
        }
        *(s16 *)(D_1F800138 + 0x50) = 3;
    } else if (k & 0x1000) {
        *(s16 *)(D_1F800138 + 0x50) = 3;
    }
}

extern s32 D_800A2914;
extern s32 D_800A2918;
extern s32 D_800A292C;
void func_8018DD38(u8 *a)
{
    u8 mask;
    u16 p;
    mask = a[0x4A] < 3;
    if (a[0x4B] < 3) {
        mask |= 2;
    }
    if (mask != 0) {
        if (a[0x44] == 0) {
            a[0x44] = 1;
        }
        if ((D_800E7E68 & 0x80) && (mask & 1) && a[0x44] != 1) {
            func_80074590(0x15, 0, 0);
            a[0x44] = 1;
        }
        if ((D_800E7E68 & 0x20) && (mask & 2) && a[0x44] != 2) {
            func_80074590(0x15, 0, 0);
            a[0x44] = 2;
        }
        if (!(a[0x44] & mask)) {
            a[0x44] = mask;
        }
        CRD_MSG2(0x36, D_800A292C);
    } else {
        a[0x44] = 0;
        CRD_MSG(0x31, D_800A2918);
    }
    p = D_800E7E68;
    if (p & 0x2000) {
        if (!(a[0x3C] & 1)) {
            *(u16 *)(D_1F800138 + 0x50) = 2;
            return;
        }
        *(u16 *)(D_1F800138 + 0x50) = 3;
        return;
    }
    if (p & 0x1000) {
        *(u16 *)(D_1F800138 + 0x50) = 3;
        return;
    }
    if ((p & 0x4000) && a[0x44] != 0) {
        func_80074590(0x11, 0, 0);
        a[0x45] = a[0x44];
        a[0x46] = a[0x44] - 1;
        CRD_MSG(0x30, D_800A2914);
        a[0] = 2;
        a[2] = 0;
        a[1] = 0;
        a[0x3F] = 0x10;
    }
}

extern s32 D_800A291C;
extern s32 D_800A2920;
extern s32 D_800A2928;
void func_8018DFEC(u8 *a)
{
    s32 k;
    s16 j;
    k = a[0x3E];
    j = k;
    if (k == 0) {
        return;
    }
    switch (j) {
    case 1:
        if ((a + a[0x46])[0x4E] == 0xFF) {
            CRD_MSG(0x30, D_800A2914);
            a[0] = 3;
            a[2] = 0;
            a[1] = 0;
            a[0x3F] = 0xC;
        } else {
            func_8018D74C(a);
        }
        break;
    case 4:
        if (!(a[0x3C] & 1)) {
            CRD_MSG(0x32, D_800A291C);
            a[3] = 1;
            a[0] = 0xE;
        } else {
            {
                CrdMenu *s;
                s32 w, w2;
                w = 0x33;
                s = &D_800BF498;
                w2 = 0x32;
                if (s->x18 != w) {
                    func_8009A5B0(s->xC, D_800A2920);
                    s->x18 = w;
                }
                if (s->x1A != w2) {
                    func_8009A5B0(s->x10, D_800A291C);
                    s->x1A = w2;
                }
            }
            a[0x53] = 1;
            a[0] = 4;
        }
        a[2] = 0;
        a[1] = 0;
        break;
    case 2:
        CRD_MSG(0x35, D_800A2928);
        a[0x50] = 0x1E;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        break;
    default:
        a[0x50] = 0;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        break;
    }
}

extern s32 D_800A297C;
void func_8018E2B4(u8 *a)
{
    s32 c;
    if ((a + a[0x46])[0x4A] != 0) {
        CRD_MSG(0x30, D_800A2914);
        a[0x50] = 0x1E;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        return;
    }
    if ((D_800E7E68 & 0x80) && a[0x53] != 0) {
        func_80074590(0x15, 0, 0);
        a[0x53] = 0;
    }
    if ((D_800E7E68 & 0x20) && a[0x53] == 0) {
        func_80074590(0x15, 0, 0);
        a[0x53] = 1;
    }
    c = -1;
    if (D_800E7E68 & 0x4000) {
        c = a[0x53];
    } else if (D_800E7E68 & 0x2000) {
        c = 1;
    }
    switch (c) {
    case 0:
        func_80074590(0x11, 0, 0);
        CRD_MSG(0x4A, D_800A297C);
        a[0] = 5;
        a[2] = 0;
        a[1] = 0;
        a[0x3F] = 0xA;
        break;
    case 1:
        func_80074590(0x14, 0, 0);
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        a[0x46] = 0xFF;
        a[0x50] = 0;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        a[0x44] = a[0x45];
        break;
    }
}

extern s32 D_800A2924;
extern s32 D_800A2980;
void func_8018E54C(u8 *a)
{
    s32 k;
    u8 j;
    k = a[0x3E];
    j = k;
    if (k == 0) {
    } else if (j == 1) {
        CRD_MSG(0x34, D_800A2924);
        a[0] = 0x10;
        a[2] = 0;
        a[1] = 0;
        a[0x3F] = 0xE;
    } else {
        CRD_MSG(0x4B, D_800A2980);
        a[0x50] = 0x1E;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
    }
}

extern s32 D_800A293C;
extern s32 D_800A2938;
void func_8018E6BC(u8 *a)
{
    u8 *e;
    s32 k;
    u16 p;
    e = *(u8 **)(a + 8);
    if ((a + a[0x46])[0x4A] != 0) {
        CRD_MSG(0x30, D_800A2914);
        a[0x50] = 0;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        return;
    }
    func_8018DB28(a);
    p = D_800E7E68;
    if (p & 0x2000) {
        func_80074590(0x14, 0, 0);
        CRD_MSG(0x30, D_800A2914);
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        a[0x46] = 0xFF;
        a[0x50] = 0;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        a[0x44] = a[0x45];
        return;
    }
    if (H(a, 0x56) == 0 && (p & 0x4000)) {
        func_80074590(0x11, 0, 0);
        k = a[0x47] * 0x3C;
        if ((e + k)[6] == 1) {
            CRD_MSG(0x3A, D_800A293C);
        } else {
            CRD_MSG(0x39, D_800A2938);
        }
        a[0x53] = 1;
        a[2] = 0;
        a[1] = 0;
        a[0] = 7;
    }
}

extern s32 D_800A2940;
extern s32 D_800A2934;
void func_8018E95C(u8 *a)
{
    s32 c;
    if ((a + a[0x46])[0x4A] != 0) {
        CRD_MSG(0x30, D_800A2914);
        a[0x50] = 0;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        return;
    }
    if ((D_800E7E68 & 0x80) && a[0x53] != 0) {
        func_80074590(0x15, 0, 0);
        a[0x53] = 0;
    }
    if ((D_800E7E68 & 0x20) && a[0x53] == 0) {
        func_80074590(0x15, 0, 0);
        a[0x53] = 1;
    }
    c = -1;
    if (D_800E7E68 & 0x4000) {
        c = a[0x53];
    } else if (D_800E7E68 & 0x2000) {
        c = 1;
    }
    switch (c) {
    case 0:
        func_80074590(0x11, 0, 0);
        CRD_MSG(0x3B, D_800A2940);
        a[0] = 8;
        a[2] = 0;
        a[1] = 0;
        a[0x3F] = 4;
        break;
    case 1:
        func_80074590(0x14, 0, 0);
        CRD_MSG2(0x38, D_800A2934);
        a[2] = 0;
        a[1] = 0;
        a[0] = 6;
        break;
    }
}

extern s32 D_800A2948;
extern s32 D_800A2944;
void func_8018EC00(u8 *a)
{
    u8 *e;
    s32 k;
    s32 one;
    if (a[0x3E] == 0) {
        return;
    }
    e = *(u8 **)(a + 8);
    one = 1;
    if (a[0x3E] == one) {
        CRD_MSG(0x3D, D_800A2948);
        k = a[0x47] * 0x3C;
        a[2] = 0;
        a[1] = 0;
        a[0] = 9;
        (a + a[0x46])[0x48] = (e + k)[4];
    } else {
        CRD_MSG(0x3C, D_800A2944);
        a[0x50] = 0x1E;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
    }
}

extern s32 D_800A2954;
void func_8018ED94(u8 *a)
{
    u16 p;
    if ((a + a[0x46])[0x4A] != 0) {
        CRD_MSG(0x30, D_800A2914);
        a[0x50] = 0;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        return;
    }
    func_8018DB28(a);
    p = D_800E7E68;
    if (p & 0x2000) {
        func_80074590(0x14, 0, 0);
        CRD_MSG(0x30, D_800A2914);
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        a[0x46] = 0xFF;
        a[0x50] = 0;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        a[0x44] = a[0x45];
        return;
    }
    if (H(a, 0x56) == 0 && (p & 0x4000)) {
        func_80074590(0x11, 0, 0);
        CRD_MSG(0x40, D_800A2954);
        a[0x53] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xB;
    }
}

extern s32 D_800A2970;
extern s32 D_800A2950;
void func_8018EFDC(u8 *a)
{
    s32 c;
    if ((a + a[0x46])[0x4A] != 0) {
        CRD_MSG(0x30, D_800A2914);
        a[0x50] = 0;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
        return;
    }
    if ((D_800E7E68 & 0x80) && a[0x53] != 0) {
        func_80074590(0x15, 0, 0);
        a[0x53] = 0;
    }
    if ((D_800E7E68 & 0x20) && a[0x53] == 0) {
        func_80074590(0x15, 0, 0);
        a[0x53] = 1;
    }
    c = -1;
    if (D_800E7E68 & 0x4000) {
        c = a[0x53];
    } else if (D_800E7E68 & 0x2000) {
        c = 1;
    }
    switch (c) {
    case 0:
        func_80074590(0x11, 0, 0);
        CRD_MSG(0x47, D_800A2970);
        a[0] = 0xC;
        a[2] = 0;
        a[1] = 0;
        a[0x3F] = 1;
        break;
    case 1:
        func_80074590(0x14, 0, 0);
        CRD_MSG2(0x3F, D_800A2950);
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xA;
        break;
    }
}

extern s32 D_800A2978;
extern s32 D_800A2974;
void func_8018F280(u8 *a)
{
    u8 *e;
    s32 k;
    s32 one;
    if (a[0x3E] == 0) {
        return;
    }
    e = *(u8 **)(a + 8);
    one = 1;
    if (a[0x3E] == one) {
        CRD_MSG(0x49, D_800A2978);
        k = a[0x47] * 0x3C;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xD;
        (a + a[0x46])[0x48] = (e + k)[4];
    } else {
        CRD_MSG(0x48, D_800A2974);
        a[0x50] = 0x1E;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
    }
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
void func_8018F414(u8 *a)
{
    CrdMenu *s;
    s32 w, m, ff;
    ff = 0xFF;
    if (a[0x46] != ff && (a + a[0x46])[0x4A] != 0) {
        w = 0x30;
        s = &D_800BF498;
        m = -1;
        if (s->x18 != w) {
            func_8009A5B0(s->xC, D_800A2914);
            s->x18 = w;
        }
        if (s->x1A != m) {
            *s->x10 = 0;
            s->x1A = m;
        }
        a[0x50] = 0;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = ff;
        a[0x46] = ff;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
    } else if (D_800E7E68 & 0x6000) {
        func_80074590(0x11, 0, 0);
        a[2] = 0;
        a[1] = 0;
        a[0] = a[3];
    }
}

void func_8018F548(u8 *a)
{
    CrdMenu *s;
    s32 w, m;
    s32 k;
    u8 j;
    k = a[0x3E];
    j = k;
    if (k == 0) {
    } else if (j == 1) {
        w = 0x30;
        s = &D_800BF498;
        m = -1;
        if (s->x18 != w) {
            func_8009A5B0(s->xC, D_800A2914);
            s->x18 = w;
        }
        if (s->x1A != m) {
            *s->x10 = 0;
            s->x1A = m;
        }
        a[0] = 2;
        a[2] = 0;
        a[1] = 0;
        a[0x3F] = 0x10;
    } else {
        a[0x50] = 0;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0x52] = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[3] = 0;
        a[2] = 0;
        a[1] = 0;
        a[0] = 0xF;
    }
}

void func_8018F660(CrdMenu *a)
{
    if (a->x41 == 0xFF) {
        return;
    }
    switch (a->x3F) {
    case 1:
    case 4:
        a->x5A = 0;
        a->x5B = 0xF;
    case 7:
    case 10:
    case 12:
    case 16:
        a->x51 = 0;
        a->x40 = 2;
        a->x3F++;
        break;
    case 14:
        a->x40 = 0;
        a->x3F++;
        a->x3D = a->x46;
        break;
    case 2:
        func_8018B020(a);
        break;
    case 5:
        func_8018B478(a);
        break;
    case 8:
        func_8018B660(a);
        break;
    case 3:
        func_8018B1A4(a);
        break;
    case 6:
        if (crd_card_event() != 0) {
            func_800808F0(a->x4);
            a->x3F = 7;
        }
        break;
    case 9:
        func_8018B7E4(a);
        break;
    case 11:
        if (func_8009C3F4(a->x46 << 4) == 0) {
            func_8001CBA8(a, a->x46);
            a->x3E = 2;
        } else {
            a->x3E = 1;
        }
        a->x3F = 0;
        a->x40 = 0;
        break;
    case 13:
        func_8018BA68(a);
        break;
    case 17:
        func_8018BF74(a);
        break;
    case 15:
        if (a->x41 == 0) {
            a->x3E = 1;
        } else {
            a->x3E = 2;
        }
        a->x3F = 0;
        break;
    }
}

extern u8 *D_800A2904;
extern u8 *D_800A2908;
void func_8018F854(CrdMenu *a)
{
    u8 *e;
    s32 dy;
    CrdRect r;
    e = a->x8;
    dy = 0;
    func_8018D418(a);
    func_8018D26C(a);
    switch (a->x0) {
    case 1:
        func_8018CCCC(a);
        break;
    case 6:
    case 10:
        func_8018CE40(a);
        break;
    case 7:
    case 11:
        func_8018C790(0x20, 0x50, 0, e + (a->x47 * 0x3C + 4));
        dy = 0x32;
    case 4:
        r.x = 0x78;
        r.y = dy + 0x78;
        r.w = 0;
        r.h = 0x10;
        crd_draw_label(D_800A2904, &r, a->x53 == 0);
        r.x = 0xB0;
        r.y = dy + 0x78;
        r.w = 4;
        r.h = 0x10;
        crd_draw_label(D_800A2908, &r, a->x53 == 1);
        break;
    }
}

extern u8 D_800E7AD8[];
extern u8 D_800D34E0[];
void func_8018FA88(u8 n)
{
    s32 i, w, m;
    CrdMenu *s;
    u8 *b;
    D_800BF498.x46 = 0xFF;
    D_800BF498.x41 = 0xFF;
    D_800BF498.x47 = 0;
    D_800BF498.x45 = 0;
    D_800BF498.x44 = 0;
    D_800BF498.x3C = n;
    D_800BF498.x3D = 0;
    D_800BF498.x3F = 0;
    D_800BF498.x40 = 0;
    D_800BF498.x3 = 0;
    D_800BF498.x2 = 0;
    D_800BF498.x1 = 0;
    D_800BF498.x0 = 0;
    D_800BF498.x8 = D_800E7AD8;
    b = D_800D34E0;
    D_800BF498.xC = b - 0x5B;
    D_800BF498.x14 = b;
    D_800BF498.x10 = b - 0xB6;
    b[-0x5B] = 0;
    b[-0xB6] = 0;
    D_800BF498.x18 = -2;
    D_800BF498.x1A = -2;
    D_800BF498.x53 = 0;
    D_800BF498.sel = 0;
    D_800BF498.x56 = 0;
    D_800BF498.x54 = 0;
    *(u16 *)(D_1F800138 + 0x50) = 1;
    for (i = 0; i < 2; i++) {
        D_800BF498.x4A[i] = 0xFC;
        D_800BF498.x4C[i] = 0;
    }
    w = 0x30;
    s = &D_800BF498;
    m = -1;
    if (s->x18 != w) {
        func_8009A5B0(s->xC, D_800A2914);
        s->x18 = w;
    }
    if (s->x1A != m) {
        *s->x10 = 0;
        s->x1A = m;
    }
}

void func_8018FBCC(void)
{
    CrdMenu *a = &D_800BF498;

    s32 k;
    u8 j;
    a->x3E = 0;
    func_8018F660(a);
    func_8018A1E8(a);
    switch (D_800BF498.x0) {
    case 0:
        func_8018DC2C(a);
        break;
    case 1:
        func_8018DD38(a);
        break;
    case 2:
        func_8018DFEC(a);
        break;
    case 3:
        k = a->x3E;
        j = k;
        if (k == 0) {
            break;
        }
        if (j == 1) {
            func_8018D74C(a);
            break;
        }
        a->x50 = 0;
        a->x44 = 0;
        a->x4A[1] = 0xFC;
        a->x4A[0] = 0xFC;
        ((u8 *)a + a->x46)[0x48] = 0;
        ((u8 *)a + a->x46)[0x4E] = 0xFF;
        a->x46 = 0xFF;
        a->x47 = 0;
        a->sel = 0;
        a->x54 = 0;
        a->x56 = 0;
        a->x3 = 0;
        a->x2 = 0;
        a->x1 = 0;
        a->x0 = 0xF;
        break;
    case 4:
        func_8018E2B4(a);
        break;
    case 5:
        func_8018E54C(a);
        break;
    case 6:
        func_8018E6BC(a);
        break;
    case 7:
        func_8018E95C(a);
        break;
    case 8:
        func_8018EC00(a);
        break;
    case 9:
        switch (a->x1) {
        case 0:
            a->x50 = 0x1E;
            a->x1++;
        case 1:
            if (a->x50 != 0) {
                a->x50--;
                if (D_800E7E68 & 0x6000) {
                    a->x50 = 0;
                }
                break;
            }
            if (!(a->x3C & 0x80)) {
                a->x0 = 3;
                a->x2 = 0;
                a->x1 = 0;
                a->x3F = 0xC;
                break;
            }
            func_8001CBA8(a, a->x46);
            *(u16 *)(D_1F800138 + 0x50) = 5;
            break;
        }
        break;
    case 10:
        func_8018ED94(a);
        break;
    case 11:
        func_8018EFDC(a);
        break;
    case 12:
        func_8018F280(a);
        break;
    case 13:
        switch (a->x1) {
        case 0:
            a->x50 = 0x1E;
            a->x1++;
        case 1:
            if (a->x50 != 0) {
                a->x50--;
                if (D_800E7E68 & 0x6000) {
                    a->x50 = 0;
                }
                break;
            }
            *(u16 *)(D_1F800138 + 0x50) = 4;
            break;
        }
        break;
    case 14:
        func_8018F414(a);
        break;
    case 15:
        if (a->x50 != 0) {
            a->x50--;
            break;
        }
        if (a->x41 != 0xFF) {
            a->x2 = 0;
            a->x1 = 0;
            a->x0 = a->x3;
        }
        break;
    case 16:
        func_8018F548(a);
        break;
    }
    func_8018F854(a);
}

#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018A1E8);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018A428);

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
    u8 pad2C[0x10];
    u8 x3C;
    u8 x3D;
    u8 x3E;
    u8 x3F;
    u8 x40;
    u8 x41;
    u8 pad42[2];
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
} CrdMenu;
extern CrdMenu D_800BF498;
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

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018B1A4);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018B478);

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

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018B7E4);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018BA68);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018BF74);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018C4B4);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018C790);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018CCCC);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018CE40);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018D26C);

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

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018DD38);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018DFEC);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018E2B4);

extern s32 D_800A2924;
extern s32 D_800A2980;
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

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018E6BC);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018E95C);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018EC00);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018ED94);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018EFDC);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018F280);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern s32 D_800A2914;

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

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018F660);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018F854);

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

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018FBCC);

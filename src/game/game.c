#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010637C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106478);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106A24);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106B98);

extern u8 *D_1F800138_5432;
extern u8 D_1F800236;
extern u8 D_800BF808[];
extern s16 D_800E7FEE;
extern u8 D_800BF880;
extern u16 D_1F800194;
/* func_80108D80, inlined */
static inline void inl_80108D80(void)
{
    u8 *p = D_1F800138_5432;

    *(s16 *)(p + 0x4A) = 1;
    *(s16 *)(p + 0x4C) = 2;
    *(s16 *)(p + 0x4E) = 3;
}
/* func_80108DA4, inlined */
static inline void inl_80108DA4(void)
{
    u8 *p;

    if (D_1F800236 >= 5) {
        func_80050894(0);
    }
    p = D_1F800138_5432;
    *(s16 *)(p + 0x4A) = 1;
    *(s16 *)(p + 0x4C) = 2;
    *(s16 *)(p + 0x4E) = 6;
}
void func_801070B4(void)
{
    u8 *p = D_1F800138_5432;
    u8 *q;

    switch (*(u16 *)(p + 0x4E)) {
    case 0:
        *(u16 *)(p + 0x4E) = 1;
        func_8006C77C();
        func_8005082C(0, 0, 0);
    case 1:
        func_80108BE4();
        if ((s8)D_800BF808[5] == 3) {
            if (D_800BF808[7] == 0) {
                func_80074BC4();
                q = D_1F800138_5432;
                *(s16 *)(q + 0x4C) = 2;
                if (D_800E7FEE != 0) {
                    D_800BF880 = 1;
                    D_1F800194 = D_800E7FEE;
                    *(s16 *)(q + 0x4E) = 0;
                } else {
                    *(s16 *)(q + 0x4E) = 2;
                }
            }
        } else if (D_800BF808[0x31] != 0 && D_800BF808[7] == 0) {
            if (D_800BF808[0x31] == 8) {
                inl_80108D80();
            } else {
                inl_80108DA4();
            }
        }
        break;
    case 2:
        *(u16 *)(p + 0x4E) = 1;
        break;
    }
}

extern u8 D_1F800136_8901;
extern u16 D_1F80017C;
typedef struct { u8 pad0[8]; s32 frames; } GameFrames;
typedef struct { u8 pad[0x48]; u16 a48, a4A, a4C, a4E; } St138;
extern St138 *D_1F800138_c102;
/* func_80108B0C, inlined */
static inline void inl_80108B0C(void)
{
    D_1F80017C++;
    ((GameFrames *)&D_800BF870)->frames++;
    if (D_1F800136_8901 == 0) {
        func_80059D28();
        func_80069B28();
        func_80026368();
        func_8007A904();
        func_80025588();
        func_8004FE84();
        func_80026C88();
        func_80022A80();
        func_8006EC44();
        func_80050DE4();
        func_8001CAC0();
    }
    if (D_1F800136_8901 < 2) {
        func_8003F9A8();
    }
    func_8010810C();
    func_80077D8C();
    func_80075A80();
}
/* func_80108BE4, inlined */
static inline void inl_80108BE4(void)
{
    D_1F80017C++;
    ((GameFrames *)&D_800BF870)->frames++;
    if (D_1F800136_8901 == 0) {
        func_80059D28();
        func_80069B28();
        func_80026368();
        func_8007B04C();
        func_80025588();
        func_8004FE84();
        func_80026C88();
        func_80022A80();
        func_8006EC44();
    }
    if (D_1F800136_8901 < 2) {
        func_8003FA44();
    }
    func_8010810C();
    func_80077D8C();
    func_80075A80();
}
void func_80107230(void)
{
    u8 *p;

    switch (*(u16 *)(D_1F800138_5432 + 0x4E)) {
    case 0:
        p = D_1F800138_5432;
        p[0x6B] = 0;
        (*(u16 *)(p + 0x4E))++;
        func_8007B18C();
        func_800796DC();
        func_800263E8();
        func_80072A78();
        func_80075240();
        func_800783DC();
        func_80078610();
        func_80074F24(D_800BF870.unk0);
        break;
    case 1:
        inl_80108B0C();
        if (D_800BF808[0x31] != 0 && D_800BF808[7] == 0) {
            if (D_800BF808[0x31] == 1) {
                inl_80108DA4();
            } else {
                inl_80108D80();
            }
        }
        break;
    case 2:
        func_8006C77C();
        (*(u16 *)(D_1F800138_5432 + 0x4E))++;
    case 3:
        inl_80108BE4();
        if (D_800BF808[0x31] != 0 && D_800BF808[7] == 0) {
            inl_80108DA4();
        }
        break;
    case 4:
        func_8006C7C4();
        *(u16 *)(D_1F800138_5432 + 0x4E) = 1;
        break;
    case 5:
        if (D_800BF870.unk0 == 7) {
            func_801128BC();
        }
        D_1F800138_c102->a4E = 1;
        inl_80108B0C();
        break;
    }
}

void func_8010766C(void)
{
    u8 *p = D_1F800138_5432;
    u8 *q;

    if (*(u16 *)(p + 0x4E) == 0) {
        (*(u16 *)(p + 0x4E))++;
        p[0x6B] = 0;
        func_8007B18C();
        func_800796DC();
        func_800263E8();
        func_80075240();
        func_800783DC();
        func_80078610();
        func_80074F24(D_800BF870.unk0);
        return;
    }
    func_80108CAC();
    if ((s8)D_800BF808[5] == 3) {
        if (D_800BF808[7] == 0) {
            if (D_800E7FEE != 0) {
                D_800BF880 = 1;
                D_1F800194 = D_800E7FEE;
            }
            *(s16 *)(D_1F800138_5432 + 0x4E) = 0;
        }
    } else if (D_800BF808[0x31] == 3 && D_800BF808[7] == 0) {
        D_800BF808[0x31] = 2;
        D_1F800236 = 2;
        q = D_1F800138_5432;
        *(s16 *)(q + 0x4A) = 1;
        *(s16 *)(q + 0x4C) = 2;
        *(s16 *)(q + 0x4E) = 6;
    }
}

void func_80107790(void)
{
    u8 *p;

    if (*(u16 *)(D_1F800138_5432 + 0x4E) == 0) {
        if (D_800BF870.unk0 == 5) {
            D_800BF870.pad1[0] = 3;
        }
        func_8007B18C();
        func_800796DC();
        func_800263E8();
        func_80072A78();
        func_80075240();
        func_800783DC();
        func_80078610();
        p = D_1F800138_5432;
        *(s16 *)(p + 0x4E) = 1;
        p[0x6B] = 0;
        func_80075024(D_800BF870.unk0);
        return;
    }
    inl_80108B0C();
    if ((s8)D_800BF808[5] == 3) {
        if (D_800BF808[7] == 0) {
            if (D_800E7FEE != 0) {
                D_800BF870.pad1[0xF] = 1;
                D_1F800194 = D_800E7FEE;
            }
            *(s16 *)(D_1F800138_5432 + 0x4E) = 0;
        }
    } else if (D_800BF808[0x31] == 3 && D_800BF808[7] == 0) {
        inl_80108DA4();
    }
}

extern u8 D_800E7E80[];
extern u8 D_800E8008[];
extern u8 D_80108F78[];
extern u8 D_80108F84[];
extern u8 D_80108F90[];
void func_801079AC(void)
{
    u8 *g = D_800E7E80;
    u8 *e = D_800E8008;
    u8 *o;

    if (D_1F800236 == 2) {
        g[0] = 0;
    } else {
        g[0] = 3;
    }
    *(s16 *)(g + 0x2E) = 0x3E8;
    *(s16 *)(g + 0x32) = -0x3E8;
    *(s16 *)(g + 0x36) = 0xBB8;
    *(s16 *)(g + 0x56) = 0xC00;
    if (D_1F800236 < 3) {
        func_8006CBD0(e, D_80108F78);
        func_8006E3B0(e, e + 0x38);
        o = func_800310F4(0x19, 0);
        *(s16 *)(o + 0x2C) = *(s16 *)(g + 0x2E);
        *(s16 *)(o + 0x2E) = *(s16 *)(g + 0x32) + 0x82;
        *(s16 *)(o + 0x30) = *(s16 *)(g + 0x36) + 0x1194;
    } else {
        if (D_1F800236 == 3) {
            func_8006CBD0(e, D_80108F84);
        } else {
            func_8006CBD0(e, D_80108F90);
        }
        o = func_800310F4(0x23, 0);
        *(s16 *)(o + 0x2C) = *(s16 *)(g + 0x2E);
        *(s16 *)(o + 0x2E) = *(s16 *)(g + 0x32);
        *(s16 *)(o + 0x30) = *(s16 *)(g + 0x36);
        *(s16 *)(e + 0x70) = 0xC00;
        func_8006EF38();
    }
    func_80074BF8(8);
}

extern u8 D_1F800234;
extern u8 D_1F80019B;
extern u8 D_800452C0[];
/* func_80108E58, inlined */
static inline void inl_80108E58(void)
{
    u8 c = D_1F800138_5432[0x6B] * 8;

    func_8007E9C8((c << 16) | (c << 8) | c, 0, 4);
    D_1F800138_5432[0x6B]--;
}
/* func_80108EBC, inlined */
static inline void inl_80108EBC(void)
{
    u8 c = -(D_1F800138_5432[0x6B] * 8);

    func_8007E9C8((c << 16) | (c << 8) | c, 1, 4);
    D_1F800138_5432[0x6B]--;
}
void func_80107AFC(void)
{
    u8 *p, *q, *r, *t, *w;

    switch (*(u16 *)(D_1F800138_5432 + 0x4E)) {
    case 0:
        D_1F800234 = 1;
        func_8007A810();
        func_800798F8();
        func_8007B0F0();
        func_801079AC();
        p = D_1F800138_5432;
        p[0x6B] = 0x1F;
        (*(u16 *)(p + 0x4E))++;
        func_8007E9C8(0xFFFFFF, 0, 4);
        func_80044BD4(D_800452C0, D_800BF870.unk0, 0, 1);
        break;
    case 1:
        inl_80108E58();
        q = D_1F800138_5432;
        if (q[0x6B] == 0) {
            (*(u16 *)(q + 0x4E))++;
        }
        goto common;
    case 2:
        if (D_1F80019B != 0) {
            r = D_1F800138_5432;
            r[0x6B] = 0x1F;
            (*(u16 *)(r + 0x4E))++;
        }
        goto common;
    case 3:
        inl_80108EBC();
        t = D_1F800138_5432;
        if (t[0x6B] == 0) {
            (*(u16 *)(t + 0x4E))++;
            func_80050894(0);
        }
    common:
        func_80059C60();
        func_8006EF38();
        func_8007B008();
        func_8003FA1C();
        break;
    case 4:
        func_80074E48();
        w = D_1F800138_5432;
        *(s16 *)(w + 0x48) = 2;
        *(s16 *)(w + 0x4A) = 1;
        *(s16 *)(w + 0x4C) = 1;
        *(s16 *)(w + 0x4E) = 0;
        break;
    }
}

void func_80107D3C(void)
{
    St138 *m = D_1F800138_c102;
    switch (m->a4E) {
    case 0:
        D_1F800234 = 1;
        m->a4E++;
        func_80044BD4(D_800452C0, D_800BF870.unk0, 0, 1);
        break;
    case 1:
        func_8003FB84();
        D_1F800138_c102->a4E++;
        break;
    case 2:
        if (g_DiscReadPending != 0) {
            m->a48 = 2;
            m->a4A = 1;
            m->a4C = 1;
            m->a4E = 0;
        } else {
            func_8003EA88();
        }
        break;
    }
}

void func_80107E20(void)
{
    switch (D_1F800138_c102->a4E) {
    case 0:
        func_80074BF8(9);
        func_8003E264();
        D_1F800138_c102->a4E++;
        D_1F800234 = 1;
        func_80044BD4(D_800452C0, D_800BF870.unk0, 0, 1);
        break;
    case 1:
        func_8003E264();
        D_1F800138_c102->a4E++;
        break;
    case 2:
        func_8003E894();
        if (g_DiscReadPending != 0) {
            func_80074E48();
            D_1F800138_c102->a48 = 2;
            D_1F800138_c102->a4A = 1;
            D_1F800138_c102->a4C = 1;
            D_1F800138_c102->a4E = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107F3C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010810C);

extern u8 D_800BF808_cee0;
extern u16 D_800E7E68;
void func_801084F8(void)
{
    u16 b;
    u8 *p;
    u8 k;

    func_8007EAE4();
    b = D_800E7E68;
    if (b & 0x10) {
        if (D_800BF808_cee0 != 0) {
            D_800BF808_cee0--;
            func_80074590(0x15, 0, 0);
        }
    } else if (b & 0x40) {
        if (D_800BF808_cee0 < 2) {
            D_800BF808_cee0++;
            func_80074590(0x15, 0, 0);
        }
    } else if (b & 0x2008) {
        D_1F800138_5432[0x6B] = 2;
        func_80074BF8(1);
    } else if (b & 0x4000) {
        D_1F800138_5432[0x6B] = D_800BF808_cee0 + 3;
        p = D_1F800138_5432;
        *(s16 *)(p + 0x50) = 0;
        k = p[0x6B];
        if (k == 3) {
            D_800BF808_cee0 = 0;
        } else {
            if (k == 4) {
                D_800BF808_cee0 = 0;
            } else {
                D_800BF808_cee0 = 1;
            }
            func_8005082C(0, 0, 0);
        }
        D_1F800136_8901 = 2;
        func_80074590(0x11, 0, 0);
    }
}

extern u8 D_800BF819_cf3c;
void func_80108624(void)
{
    u8 *p = D_1F800138_5432;
    s32 s = *(u16 *)(p + 0x50);

    switch (s) {
    case 0:
    case 1:
        *(s16 *)(p + 0x50) = s + 1;
        break;
    case 2:
        *(s16 *)(p + 0x50) = 3;
        func_80050894(0);
        D_1F800136_8901 = 2;
        func_8007AC6C();
        break;
    case 3:
        if (func_800346BC() != 0) {
            *(s16 *)(D_1F800138_5432 + 0x50) = 0;
            D_1F800138_5432[0x6B] = 0;
            D_1F800136_8901 = 0;
            D_800BF819_cf3c = 8;
            func_80050970();
        }
        break;
    }
}

s32 func_801086E0(void) {
    void *temp_v0;

    temp_v0 = *(void **)0x1F800138;
    M2C_FIELD(temp_v0, s16 *, 0x48) = 2;
    M2C_FIELD(temp_v0, s16 *, 0x4A) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x4C) = 0;
    M2C_FIELD(temp_v0, s8 *, 0x69) = 0;
    func_8007A8E0();
    return func_8007B38C();
}

extern u8 D_1F8001FF;
extern s16 D_1F800278;
extern u8 D_1F800206;
void func_80108720(void)
{
    u8 *p = D_1F800138_5432;

    *(s16 *)(p + 0x48) = 2;
    *(s16 *)(p + 0x4A) = 1;
    *(s16 *)(p + 0x4C) = 0;
    p[0x69] = 0;
    D_1F8001FF = 0xFF;
    D_1F800278 = 0;
    func_8007B3F4();
    D_1F800206 = 0;
    D_1F800236 = 0;
    D_1F800234 = 0;
}

void func_80108784(void)
{
    switch (*(u16 *)(D_1F800138_5432 + 0x4A)) {
    case 0:
        func_8010882C();
        break;
    case 1:
        func_801088D8();
        break;
    case 2:
        func_80106478();
        break;
    case 3:
        func_80106A24();
        break;
    case 4:
        func_801089C4();
        break;
    case 5:
        func_80108A60();
        break;
    }
}

void func_8010882C(void)
{
    u8 pad[0x10];
    u8 *p = D_1F800138_5432;

    switch (*(u16 *)(p + 0x4C)) {
    case 0:
        switch (*(u16 *)(p + 0x4E)) {
        case 0:
            func_8005082C(0, 0, 0);
            p = D_1F800138_5432;
            *(s16 *)(p + 0x50) = 0;
            (*(s16 *)(p + 0x4E))++;
            break;
        case 1:
            func_80109450();
            break;
        }
        break;
    case 1:
        *(s16 *)(p + 0x4C) = 0;
        (*(s16 *)(p + 0x4A))++;
        break;
    }
}

extern u8 D_80108F60[];
void func_801088D8(void)
{
    switch (*(u16 *)(D_1F800138_5432 + 0x4C)) {
    case 0:
        func_8005245C();
        func_80044BD4(D_800452C0, D_800BF870.unk0, 0, 2);
    case 1:
        D_1F800234 = 0;
        *(s16 *)(D_1F800138_5432 + 0x4C) = D_80108F60[D_800BF870.unk0];
        break;
    case 2:
        func_80106B98();
        break;
    case 3:
        func_801070B4();
        break;
    case 4:
        func_80107230();
        break;
    case 5:
        func_8010766C();
        break;
    case 6:
        func_80107790();
        break;
    }
}

void func_801089C4(void)
{
    switch (*(u16 *)(D_1F800138_5432 + 0x4C)) {
    case 0:
        func_80074BC4();
        (*(s16 *)(D_1F800138_5432 + 0x4C))++;
        break;
    case 1:
        D_1F800138_5432[0x69] = 0;
        D_1F800138_5432[0x6A] = 0;
        D_1F800138_5432[0x6B] = 0;
        *(s16 *)(D_1F800138_5432 + 0x4A) = 0;
        *(s16 *)(D_1F800138_5432 + 0x4C) = 0;
        *(s16 *)(D_1F800138_5432 + 0x4E) = 0;
        func_80052078(1);
        break;
    }
}

void func_80108A60(void)
{
    u8 *p;

    switch (*(u16 *)(D_1F800138_5432 + 0x4C)) {
    case 0:
    case 9:
        p = D_1F800138_5432;
        *(s16 *)(p + 0x48) = 2;
        *(s16 *)(p + 0x4A) = 1;
        *(s16 *)(p + 0x4C) = 0;
        *(s16 *)(p + 0x4E) = 0;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        func_80107AFC();
        break;
    case 7:
        func_80107E20();
        break;
    case 5:
    case 6:
        func_80107D3C();
        break;
    case 8:
        func_80107F3C();
        break;
    }
}

void func_80108B0C(void)
{
    D_1F80017C++;
    ((GameFrames *)&D_800BF870)->frames++;
    if (D_1F800136_8901 == 0) {
        func_80059D28();
        func_80069B28();
        func_80026368();
        func_8007A904();
        func_80025588();
        func_8004FE84();
        func_80026C88();
        func_80022A80();
        func_8006EC44();
        func_80050DE4();
        func_8001CAC0();
    }
    if (D_1F800136_8901 < 2) {
        func_8003F9A8();
    }
    func_8010810C();
    func_80077D8C();
    func_80075A80();
}

void func_80108BE4(void)
{
    D_1F80017C++;
    ((GameFrames *)&D_800BF870)->frames++;
    if (D_1F800136_8901 == 0) {
        func_80059D28();
        func_80069B28();
        func_80026368();
        func_8007B04C();
        func_80025588();
        func_8004FE84();
        func_80026C88();
        func_80022A80();
        func_8006EC44();
    }
    if (D_1F800136_8901 < 2) {
        func_8003FA44();
    }
    func_8010810C();
    func_80077D8C();
    func_80075A80();
}

void func_80108CAC(void)
{
    D_1F80017C++;
    ((GameFrames *)&D_800BF870)->frames++;
    if (D_1F800136_8901 == 0) {
        func_80026368();
        func_8007A904();
        func_80059D28();
        func_80025588();
        func_8004FE84();
        func_8006EC44();
        func_80050DE4();
    }
    if (D_1F800136_8901 < 2) {
        func_8010B328();
    }
    func_8010810C();
    func_80077D8C();
    func_80075A80();
}

s32 func_80108D64(void) {
    void *temp_v0;

    temp_v0 = *(void **)0x1F800138;
    M2C_FIELD(temp_v0, s16 *, 0x4A) = 3;
    M2C_FIELD(temp_v0, s16 *, 0x4C) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x4E) = 0;
    return (s32) temp_v0;
}

void func_80108D80(void)
{
    u8 *p = D_1F800138_5432;

    *(s16 *)(p + 0x4A) = 1;
    *(s16 *)(p + 0x4C) = 2;
    *(s16 *)(p + 0x4E) = 3;
}

void func_80108DA4(void)
{
    u8 *p;

    if (D_1F800236 >= 5) {
        func_80050894(0);
    }
    p = D_1F800138_5432;
    *(s16 *)(p + 0x4A) = 1;
    *(s16 *)(p + 0x4C) = 2;
    *(s16 *)(p + 0x4E) = 6;
}

void func_80108DF4(void)
{
    u8 *p;

    func_8007B18C();
    func_800796DC();
    func_800263E8();
    func_80072A78();
    func_80075240();
    func_800783DC();
    func_80078610();
    p = D_1F800138_5432;
    *(s16 *)(p + 0x4E) = 1;
    p[0x6B] = 0;
}

void func_80108E58(void)
{
    u8 c = D_1F800138_5432[0x6B] * 8;

    func_8007E9C8((c << 16) | (c << 8) | c, 0, 4);
    D_1F800138_5432[0x6B]--;
}

void func_80108EBC(void)
{
    u8 c = -(D_1F800138_5432[0x6B] * 8);

    func_8007E9C8((c << 16) | (c << 8) | c, 1, 4);
    D_1F800138_5432[0x6B]--;
}

extern s8 D_1F800136[];
extern s8 D_1F800138[];
extern s8 D_800BF819;
s32 func_80108F24(void) {
    M2C_FIELD(*((void **)D_1F800138), s8 *, 0x6B) = 0;
    *((s8 *)D_1F800136) = 0;
    D_800BF819 = 8;
    return func_80050970();
}

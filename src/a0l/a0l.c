#include "common.h"
#include "game.h"
#include "m2c.h"

extern u16 D_800BF812;

void func_80109208(u8 *a)
{
    u16 limit = D_800BF812;

    if (!(a[0x145] & 1)) {
        if (*(s16 *)(a + 0x32) >= (s16)limit - *(s16 *)(a + 0x62)) {
            *(u16 *)(a + 0x32) = limit - *(u16 *)(a + 0x62);
            func_80022C78(a);
        }
    }
}

extern u8 D_800BF808[];

void func_80109268(u8 *a)
{
    u8 *s = D_800BF808;
    u16 limit;

    if (s[0xE] != 0) {
        limit = *(u16 *)(s + 0xA);
        if (!(a[0x145] & 1)) {
            if (*(s16 *)(a + 0x32) >= (s16)limit - *(s16 *)(a + 0x62)) {
                *(u16 *)(a + 0x32) = limit - *(u16 *)(a + 0x62);
                func_80022C78(a);
            }
        }
    }
}


s32 func_801092D8(void) {
    return *(s32 *)0x1F800080;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801092E8);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801094B8);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingIllustrationTransition);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010983C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingArea2CameraSequence);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingArea4CameraSequence);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingArea5MysteryCameraSequence);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010A680);

extern u8 D_800BFA55;
extern u8 D_80114F5C[];
extern u8 *D_800BF544;
extern u8 *D_800ED8C8;
extern s16 D_800E7ED6;
extern u8 D_8011605C[];

void func_8010A768(u8 *a)
{
    if (a[2] == 0) {
        D_800BFA55 = 0;
        a[0x64] |= 0x80;
        func_8006CBD0(a, D_80114F5C);
        func_8006E3B0(a, a + 0x38);
        a[2]++;
    }
}


void func_8010A7D0(void) {
}


void func_8010A7D8(void) {
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010A7E0);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010A958);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010AA4C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010AD40);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B0B8);

void func_8010B1B8(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    f_DispatchEndingAreaCameraSequence(func_80112DEC(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B200);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B4EC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B61C);

extern u16 *D_800ECF78;

void func_8010B8EC(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B918);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010BB64);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010BCA8);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010BE30);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010C1D8);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010C7F4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010CA30);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingIllustrationPanels);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010CF6C);

extern s32 D_8011A6C4;
extern s32 D_8011A6C8;
extern s32 D_8011A6CC;
extern s32 D_8011A6D0;
void f_ResetEndingIllustrationState(void) {
    D_8011A6C4 = 0;
    D_8011A6C8 = 0;
    D_8011A6CC = -0x100;
    D_8011A6D0 = 0;
}

void func_8010D058(s32 i, s32 b, s32 c, s32 d, s32 e)
{
    u8 *m = D_800BF544;

    func_80083DE0(m, b, c, d, e);
    func_80083C30(D_800ED8C8 + i * 4, m);
    D_800BF544 = m + 0xC;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingContinuePrompt);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingScriptController);

extern u8 D_800BF841;
s32 func_8010D460(void *arg0) {
    D_800BF841 = M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}


s32 func_8010D474(void *arg0) {
    M2C_FIELD(arg0, u8 *, 7) = (u8) (M2C_FIELD(arg0, u8 *, 7) + M2C_FIELD(arg0, u8 *, 0x72));
    return 1;
}

void func_8010D490(u8 *a)
{
    u8 *s;

    if (a[5] == 0) {
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            s = D_800BF808;
            s[0x31] = 3;
            *(s16 *)(s + 0x32) = 0x1503;
            a[5]++;
        }
    }
    f_UpdateEndingContinuePrompt(a);
}

void func_8010D504(u8 *a)
{
    u8 *s;

    func_80041098(a);
    if (a[0x70] == 0xFF) {
        s = D_800BF808;
        s[7] = 2;
        s[0x31] = 3;
        *(s16 *)(s + 0x32) = 0x1505;
        a[4] = 3;
    }
}


void func_8010D558(void *arg0) {
    func_80041098();
    if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010D590);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010D8F0);


s32 func_8010DB44(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x72) + arg0;
    M2C_FIELD(temp_v1, u8 *, 4) = (u8) (M2C_FIELD(temp_v1, u8 *, 4) + 1);
    return 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010DB68);


s32 func_8010DF90(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x72) + arg0;
    M2C_FIELD(temp_v1, u8 *, 4) = (u8) (M2C_FIELD(temp_v1, u8 *, 4) + 1);
    return 1;
}


s32 func_8010DFB4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x5E) = 1;
    return 1;
}

s32 func_8010DFC4(u8 *a)
{
    if (D_800BF841 != 0) {
        a[0x5E] = 1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010DFEC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E3D4);

void func_8010E438(s32 a)
{
    func_80041718(a, 1, 0);
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E45C);

extern s32 D_800BF850;
s32 func_8010E51C(void *arg0) {
    D_800BF850 = (s32) M2C_FIELD(arg0, s16 *, 0x72);
    return 1;
}

void func_8010E530(u8 *a)
{
    *(s16 *)(a + 0x56) = 0x1BC;
    D_800E7ED6 = 0x309;
    a[0xB] = (a[0xB] & 0xC0) | 0x80;
    func_80041718(a, 3, 0);
    func_80040D68(a, D_8011605C);
    a[0x70] = 2;
}


void func_8010E598(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        func_80041098();
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
    }
}

extern s16 D_1F800160;
extern s16 D_1F800164;
extern u8 *D_1F80024C;
void func_80111744();

void func_8010E5F0(u8 *a)
{
    a[0xB] = (a[0xB] & 0xC0) | 0x80;
    func_80041718(a, 3, 0);
    *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
    D_1F80024C = a;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E650);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingCompletionBranchScript);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E8B8);

s32 func_8010EB90(u8 *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80111744;
        r[3] = 5;
        r[0x5E] = a[0xBF] - 1;
        return 1;
    }
    return 0;
}

extern s8 D_800BFA58;
extern M2C_UNK D_800E7E80;
s32 func_8010EBF0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xBF) == 1) {
        D_800BFA58 = 0;
    } else {
        D_800BFA58 = 1;
    }
    func_801094B8(&D_800E7E80);
    return 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010EC30);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010EF28);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010F250);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010F34C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010F56C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010FA48);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010FC58);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010FDB4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010FF10);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80110094);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80110218);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8011039C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80110548);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801106A8);

extern s16 D_800A4F7E;
extern M2C_UNK D_801179E0;
extern M2C_UNK D_80118AA8;
extern M2C_UNK D_80119AA0;
void func_80110774(void) {
    func_80075448(0xA, &D_801179E0, 0x16, D_800A4F7E);
    func_80075448(0xB, &D_80118AA8, 0x10, D_800A4F7E);
    func_80075448(0xC, &D_80119AA0, 0x10, D_800A4F7E);
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801107DC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80110918);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80110A44);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80110BA0);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111094);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111298);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801115A4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111744);

void func_80111BF4(void *a)
{
    func_80051B70(a, 0xC, 0x5);
    func_800517F8(a);
}


void func_80111C28(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111C34);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111CFC);

void func_80111DB0(void *a)
{
    func_80051B70(a, 0xC, 0x6);
    func_800517F8(a);
}


void func_80111DE4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111DF0);

extern void *D_800ECF80;
extern u8 D_8011A6D4[];

void func_80111EB0(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    if (a[0x5E] == 0) {
        func_80077B38(a, D_8011A6D4, 1);
    } else {
        func_80077B38(a, D_8011A6D4, 2);
    }
    a[0xB] = 0x10;
    *(s16 *)(a + 0x2E) = 0x640;
    *(s16 *)(a + 0x32) = -0x35C;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    *(s16 *)(a + 0x36) = 0x960;
}

u8 *func_80111F3C(void *a, u8 b)
{
    u8 *r = func_80072DDC(0, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80111744;
        r[3] = 6;
        r[0x5E] = b;
        *(void **)(r + 0x10) = a;
    }
    return r;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111FA4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8011208C);


void func_80112130(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8011A6D4, 0x7);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}


void func_80112180(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_AdvanceEndingScriptedPresentation);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801122B4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112660);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801129D4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112AE0);

typedef struct {
    s16 x, y, w, h;
} Rect16;
typedef struct {
    u32 *vlcbuf[2];
    s32 vlcid;
    u16 *imgbuf[2];
    s32 imgid;
    Rect16 rect[2];
    s32 rectid;
    Rect16 slice;
    s32 isdone;
} DecEnv;
typedef struct {
    u16 id;
    u16 type;
    u16 secCount;
    u16 nSectors;
    u32 frameCount;
    u32 bsHeadSize;
    u16 width;
    u16 height;
} StHeader;
extern u8 *D_1F800138;
extern u32 D_1F800250;
typedef struct {
    u32 unk0;
    u8 *buf;
    u32 unk8;
} MovieDef;
extern MovieDef D_8011A6AC[];

void func_80112BA0(s32 a, s32 b)
{
    u8 *buf = D_8011A6AC[D_1F800138[0x69]].buf;

    func_8009C620(0);
    func_8009C8BC(b);
    func_80089870(buf + 0x28000, 0x20);
    func_8008CEB0(0, 1, -1, 0, 0);
    func_80112D98(a);
}

typedef struct {
    u32 *vlcbuf[2];
    s32 vlcid;
} VlcEnv;

s32 func_80112C40(VlcEnv *dec, s32 b)
{
    s32 cnt = 2000;
    u32 *next;

    while ((next = (u32 *)func_80112CDC(dec, b)) == NULL) {
        if (--cnt == 0) {
            return -1;
        }
    }
    dec->vlcid = 1 - dec->vlcid;
    func_8009CCE0(next, dec->vlcbuf[dec->vlcid]);
    func_8008CF40(next);
    return 0;
}

u32 *func_80112CDC(DecEnv *dec, u32 limit)
{
    u32 *addr;
    StHeader *sector;
    s32 cnt = 2000;
    u32 n;

    while (func_8008D030(&addr, &sector)) {
        if (--cnt == 0) {
            return 0;
        }
    }
    if (sector->frameCount >= limit) {
        *(s16 *)(D_1F800138 + 0x4E) = 7;
    }
    n = sector->frameCount;
    dec->rect[0].w = dec->rect[1].w = sector->width;
    dec->rect[0].h = dec->rect[1].h = sector->height;
    D_1F800250 = n;
    dec->slice.h = sector->height;
    return addr;
}

void func_80112D98(s32 a)
{
    s32 n = 0x1C0;

    do {
        while (func_80089BAC(2, a, 0) == 0) {
        }
    } while (func_8008CC30(n) == 0);
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112DEC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_DispatchEndingAreaCameraSequence);

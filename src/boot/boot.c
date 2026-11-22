#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80010D54);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_800111B4);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_8001138C);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80011544);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80011654);

extern s32 D_800253E4;
void func_800116CC(s32 arg0, M2C_UNK arg1) {
    s32 temp_s1;

    temp_s1 = D_800253E4;
    DecDCTReset(0);
    DecDCToutCallback(arg1);
    StSetRing(temp_s1 + 0x18000, 0x20);
    StSetStream(0, 1, -1, 0, 0);
    func_80011904(arg0);
}

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_8001174C);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_800117D0);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80011864);

void func_80011904(u8 *pos)
{
    u8 mode = 0x80;

    do {
        while (CdControl(2, pos, 0) == 0) {
        }
        while (CdControl(0xE, &mode, 0) == 0) {
        }
        VSync(3);
    } while (CdRead2(0x1C0) == 0);
}

typedef struct {
    u32 mode;
    void *crect;
    u32 *caddr;
    void *prect;
    u32 *paddr;
} TimImage;

void func_80011974(u32 *addr)
{
    TimImage t;

    OpenTIM(addr);
    ReadTIM(&t);
    LoadImage(t.prect, t.paddr);
    if (t.mode & 8) {
        LoadImage(t.crect, t.caddr);
    }
    DrawSync(0);
}

extern M2C_UNK D_800253A4;
void func_800119D8(void) {
    _96_init();
    LoadExec(&D_800253A4, 0x80200000, 0);
}

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80011A0C);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80011A78);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_800123B0);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80012584);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80012674);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_800127E0);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80012954);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80012B08);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80012B9C);

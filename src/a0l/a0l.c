#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80109208);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80109268);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010A768);

void func_8010A7D0(void) {
}

void func_8010A7D8(void) {
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010A7E0);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010A958);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010AA4C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010AD40);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B0B8);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B1B8);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B200);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B4EC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B61C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B8EC);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010D058);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010D490);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010D504);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010DFC4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010DFEC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E3D4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E438);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E45C);

extern s32 D_800BF850;
s32 func_8010E51C(void *arg0) {
    D_800BF850 = (s32) M2C_FIELD(arg0, s16 *, 0x72);
    return 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E530);

void func_8010E598(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        func_80041098();
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
    }
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E5F0);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E650);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingCompletionBranchScript);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E8B8);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010EB90);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111BF4);

void func_80111C28(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111C34);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111CFC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111DB0);

void func_80111DE4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111DF0);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111EB0);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111F3C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111FA4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8011208C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112130);

void func_80112180(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_AdvanceEndingScriptedPresentation);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801122B4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112660);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801129D4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112AE0);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112BA0);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112C40);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112CDC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112D98);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112DEC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_DispatchEndingAreaCameraSequence);

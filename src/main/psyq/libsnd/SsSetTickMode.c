// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
typedef void (*SndSeqTickEnv_tick_cb_t)(void);
typedef void (*SndSeqTickEnv_vsync_cb_t)();
struct SndSeqTickEnv {
               s32 tick_mode;
               s32 manual_tick;
               SndSeqTickEnv_tick_cb_t tick_cb;
               SndSeqTickEnv_vsync_cb_t vsync_cb;
               u8 vsync_tick;
               u8 unk11;
               u8 alarm_tick;
               int unk14;
};
extern struct SndSeqTickEnv D_800AC424;
extern u32 D_80104C2C;
long GetVideoMode (void);

void SsSetTickMode(long tick_mode) {
    int video_mode;
    video_mode = GetVideoMode();
    if (tick_mode & 0x1000) {
        D_800AC424.manual_tick = 1;
        D_800AC424.tick_mode = tick_mode & 0xFFF;
    } else {
        D_800AC424.manual_tick = 0;
        D_800AC424.tick_mode = tick_mode;
    }
    if (D_800AC424.tick_mode < 6) {
        switch (D_800AC424.tick_mode) {
        case 4:
            D_80104C2C = 50;
            if (video_mode != 1) {
                D_800AC424.tick_mode = 50;
            } else {
                D_800AC424.tick_mode = 5;
            }
            return;
        case 1:
            D_80104C2C = 60;
            if (video_mode == 0) {
                D_800AC424.tick_mode = 5;
            } else {
                D_800AC424.tick_mode = 60;
            }
            return;
        case 3:
            D_80104C2C = 120;
            return;
        case 2:
            D_80104C2C = 240;
            return;
        case 5:
            if (video_mode == 0) {
                D_80104C2C = 60;
            } else if (video_mode == 1) {
                D_80104C2C = 50;
            } else {
                D_80104C2C = 60;
            }
            break;
        case 0:
            if (video_mode == 0) {
                D_80104C2C = 60;
            } else if (video_mode == 1) {
                D_80104C2C = 50;
            } else {
                D_80104C2C = 60;
            }
            return;
        default:
            D_80104C2C = 60;
            return;
        }
    } else {
        D_80104C2C = D_800AC424.tick_mode;
    }
}

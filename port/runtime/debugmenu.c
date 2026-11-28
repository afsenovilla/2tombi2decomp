/* --debug-menu (port only, opt-in; docs/PORT.md §0.5): an in-game debug menu drawn over the displayed picture.
 * Adapted from Tombi-Decomp's port2/runtime/debugmenu.c (MIT, same author): the same menu, keys, 5x7 font and hook
 * points, with Tomba! 2's data (USA addresses).
 *
 * Open / close: Select+L1+R1 (pad or keyboard) or F1 (--window: the viewer sends that combination).  While it is
 * open the game gets no buttons.  Up/Down pick a line, Left/Right change its value (L2 held: steps of 10), Cross
 * applies / toggles, Triangle or Start closes.
 *
 * Hooks (all inert unless --debug-menu / --noclip / --debug-warp is given, so the default run is byte-identical):
 *   shims/pad.c      port_pad_vblank -> port_debug_pad     (input, live cheats, the warp request: memory writes only,
 *                                                           as --poke does)
 *   shims/gpu.c      port_gpu_vblank -> port_debug_draw    (the overlay, drawn into the RGB copy of the displayed
 *                                                           frame that the window / a dump gets; VRAM is not touched)
 *   runtime/sys_lookup.c port_lookup -> port_debug_hook    (noclip: the wall probes of the player return "no
 *                                                           contact")
 *   tools/view/tomba2_view.c  F1 -> Select+L1+R1
 * The game data (docs/PORT.md §0.5): the player actor 0x800E7E80 (position 16.16 at +0x2C/+0x30/+0x34, speed +0x44,
 * direction +0x48..+0x4C, vitality s16 +0x16E and its displayed copy +0x170, state +4), the game state 0x800BF870
 * (area +0, arrival +1, AP s32 +4, max vitality +0xD), 0x800BF841 (set: the player's update is skipped), the area transition (0x800BF839 = 1 request, 0x800BF83A u16
 * destination area << 8 | arrival, scratchpad 0x1F800236 = 7: how the boss areas and A0F's exits leave). */
#include "port_runtime.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;

int port_debug_menu;          /* --debug-menu */
int port_debug_noclip;        /* the menu's line, or --noclip */
int port_debug_hooks;         /* port_lookup asks port_debug_hook (noclip or fly on) */
static int menu_open, cursor, fly, inf_hp, inf_ap, overlay, speed, saved_realtime = -1;
static int w_area = 1, w_spawn = 0;
static u16 prev, swallow;
static int fps_x100, fps_n0;
static unsigned long long fps_t0;
static char msg[48];
static int msg_t;
static int warp_frame = -1, warp_area, warp_spawn;   /* --debug-warp FRAME:AREA:SPAWN (retried until in gameplay) */
static int warp_pending = -1;                         /* the menu's WARP NOW (area << 8 | spawn) */

#define PLAYER       ((u8 *)0x800E7E80u)
#define P_(o, T)     (*(T *)(PLAYER + (o)))
#define G_(o, T)     (*(T *)(0x800BF870u + (o)))
#define G_AREA       G_(0x000, u8)
#define G_ARRIVAL    G_(0x001, u8)
#define G_AP         G_(0x004, s32)
#define G_MAXHP      G_(0x00D, u8)
#define T_REQUEST    (*(u8 *)0x800BF839u)
#define T_DEST       (*(u16 *)0x800BF83Au)
#define T_MODE       (*(u8 *)0x1F800236u)
#define DEMO_MODE    (*(u8 *)0x1F80019Au)

extern int port_realtime, port_hz;
static int fmt(char *b, int n, const char *f, ...) {
    __builtin_va_list ap;
    __builtin_va_start(ap, f);
    int r = port_vsnprintf(b, n, f, ap);
    __builtin_va_end(ap);
    return r;
}
static int is_area_resident(void) {
    extern const char *port_ovl_resident(u32p vram);
    const char *f = port_ovl_resident(0x80108F9Cu);   /* "BIN/A0x.BIN" */
    return f && f[4] == 'A' && f[5] == '0';
}
/* gameplay: an area overlay resident, the player actor running (state 1), no transition under way, no attract demo */
static int in_gameplay(void) {
    return is_area_resident() && P_(4, u8) == 1 && T_REQUEST == 0 && DEMO_MODE != 1 && G_AREA <= 0x15;
}
static void say(const char *s) {
    fmt(msg, sizeof msg, "%s", s);
    msg_t = 150;
    port_printf("[debug] frame %d: %s\n", port_frame, s);
}

/* ---- port_lookup hooks ---- */
typedef u32 (*fn8)(u32, u32, u32, u32, u32, u32, u32, u32);
static void *orig_radial, *orig_dir;
static u32 call_orig(void *f, u32 addr, u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    if (f) return ((fn8)f)(a0, a1, a2, a3, a4, a5, a6, a7);
    port_mips_pending = addr;
    return port_mips_entry(a0, a1, a2, a3, a4, a5, a6, a7);
}
/* f_ResolveActorRadialTerrainContact 0x80045CAC / f_ResolveActorDirectionalTerrainContact 0x80046E2C: the horizontal
   terrain probes (walls; the floor is f_ResolveTerrainProbeVerticalContact): 0 = no contact for the player */
static u32 noclip_radial(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    if (port_debug_noclip && a0 == (u32)PLAYER) return 0;
    return call_orig(orig_radial, 0x80045CACu, a0, a1, a2, a3, a4, a5, a6, a7);
}
static u32 noclip_dir(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    if (port_debug_noclip && a0 == (u32)PLAYER) return 0;
    return call_orig(orig_dir, 0x80046E2Cu, a0, a1, a2, a3, a4, a5, a6, a7);
}
/* fly: the player's update is skipped as the game itself does while 0x800BF841 is set (func_80059D28: no call of
   func_8005950C / the area's own player update); the d-pad moves the position from the vblank (fly_move) */
#define FREEZE (*(u8 *)0x800BF841u)
static int frozen;
static void fly_move(u16 b) {
    int v = (b & 0x4000) ? 16 : 4;   /* Cross held: fast */
    if (!fly || !in_gameplay()) {
        if (frozen) { FREEZE = 0; frozen = 0; }
        return;
    }
    FREEZE = 1;
    frozen = 1;
    if (b & 0x0080) P_(0x2C, s32) -= v << 16;
    if (b & 0x0020) P_(0x2C, s32) += v << 16;
    if (b & 0x0010) P_(0x34, s32) += v << 16;   /* up: away from the camera */
    if (b & 0x0040) P_(0x34, s32) -= v << 16;
    if (b & 0x0400) P_(0x30, s32) -= v << 16;   /* L1: up (y grows downwards) */
    if (b & 0x0800) P_(0x30, s32) += v << 16;   /* R1: down */
    P_(0x44, s16) = 0;
    P_(0x4A, s16) = 0;
}
void *port_debug_hook(u32p a, void *f) {
    if (a == 0x80045CACu && port_debug_noclip) { if (f != (void *)noclip_radial) orig_radial = f; return (void *)noclip_radial; }
    if (a == 0x80046E2Cu && port_debug_noclip) { if (f != (void *)noclip_dir) orig_dir = f; return (void *)noclip_dir; }
    return f;
}
static void update_hooks(void) { port_debug_hooks = port_debug_noclip; }

/* command-line test hooks (main_port.c) */
void port_debug_noclip_on(void) { port_debug_noclip = 1; update_hooks(); }
void port_debug_warp_arg(const char *s) {   /* FRAME:AREA:SPAWN (AREA in hex: 1 = A01, 10 = A0G) */
    int v[3] = {0, 0, 0}, k = 0;
    for (; *s && k < 3; s++) {
        if (*s == ':') { k++; continue; }
        int c = *s | 32, d = c >= '0' && c <= '9' ? c - '0' : c >= 'a' && c <= 'f' ? c - 'a' + 10 : -1;
        if (d < 0) port_fatal("--debug-warp FRAME:AREA:SPAWN");
        v[k] = v[k] * (k == 1 ? 16 : 10) + d;
    }
    warp_frame = v[0]; warp_area = v[1]; warp_spawn = v[2];
    port_debug_menu = 1;
}

/* ---- menu lines ---- */
enum { L_NOCLIP, L_FLY, L_HP, L_AP, L_AREA, L_SPAWN, L_WARP, L_OVERLAY, L_SPEED, N_LINES };
static const char *onoff(int v) { return v ? "ON" : "OFF"; }
static const char *area_name(int a) {
    static char b[4];
    b[0] = 'A'; b[1] = '0'; b[2] = "0123456789ABCDEFGHIJKL"[a]; b[3] = 0;
    return b;
}
static void line_text(int i, char *b, int n) {
    static const char *speed_names[] = {"NORMAL", "SLOW 1/2", "FAST"};
    switch (i) {
    case L_NOCLIP: fmt(b, n, "NOCLIP (WALLS)      %s", onoff(port_debug_noclip)); break;
    case L_FLY: fmt(b, n, "FLY (DPAD L1 R1)    %s", onoff(fly)); break;
    case L_HP: fmt(b, n, "INFINITE VITALITY   %s", onoff(inf_hp)); break;
    case L_AP: fmt(b, n, "MAX AP (9999999)    %s", onoff(inf_ap)); break;
    case L_AREA: fmt(b, n, "WARP AREA    < %s >", area_name(w_area)); break;
    case L_SPAWN: fmt(b, n, "WARP SPAWN   < %d >", w_spawn); break;
    case L_WARP: fmt(b, n, "WARP NOW            [X]"); break;
    case L_OVERLAY: fmt(b, n, "INFO OVERLAY        %s", onoff(overlay)); break;
    case L_SPEED: fmt(b, n, "SPEED  < %s >", speed_names[speed]); break;
    }
}
static int wrap(int v, int n) { return (v % n + n) % n; }
static void adjust(int i, int d) {
    switch (i) {
    case L_AREA: w_area = wrap(w_area + d, 0x16); w_spawn = 0; break;
    case L_SPAWN: w_spawn = wrap(w_spawn + d, 64); break;
    case L_SPEED: speed = wrap(speed + d, 3); break;
    default: break;
    }
}
static void activate(int i) {
    switch (i) {
    case L_NOCLIP: port_debug_noclip = !port_debug_noclip; say(port_debug_noclip ? "NOCLIP ON" : "NOCLIP OFF"); break;
    case L_FLY: fly = !fly; say(fly ? "FLY ON" : "FLY OFF"); break;
    case L_HP: inf_hp = !inf_hp; say(inf_hp ? "INFINITE VITALITY ON" : "INFINITE VITALITY OFF"); break;
    case L_AP: inf_ap = !inf_ap; say(inf_ap ? "MAX AP ON" : "MAX AP OFF"); break;
    case L_AREA: case L_SPAWN: case L_WARP: warp_pending = w_area << 8 | w_spawn; break;
    case L_OVERLAY: overlay = !overlay; break;
    case L_SPEED: speed = (speed + 1) % 3; break;
    }
    update_hooks();
}
/* the area transition the game's own exits make (A0A..A0E's boss ends, A0F): destination, request, mode 7 */
static int do_warp(int area, int spawn) {
    char b[48];
    if (!in_gameplay()) return 0;
    if (fly) { fly = 0; fly_move(0); }
    T_DEST = (u16)(area << 8 | spawn);
    T_REQUEST = 1;
    T_MODE = 7;
    fmt(b, sizeof b, "WARP TO %s SPAWN %d", area_name(area), spawn);
    say(b);
    return 1;
}

/* every vblank (pad.c), after the host input is merged: returns the buttons the game sees */
void port_debug_pad(u16 *buttons) {
    u16 now = *buttons, press = now & ~prev;
    int combo = (now & 0x0C01) == 0x0C01 && (prev & 0x0C01) != 0x0C01;
    prev = now;
    swallow &= now;
    {
        unsigned long long t = port_time_us();
        if (!fps_t0) { fps_t0 = t; fps_n0 = port_frame; }
        else if (t - fps_t0 >= 500000ull) {
            fps_x100 = (int)((unsigned long long)(port_frame - fps_n0) * 100000000ull / (t - fps_t0));
            fps_t0 = t; fps_n0 = port_frame;
        }
    }
    if (msg_t > 0) msg_t--;
    if (warp_frame >= 0 && port_frame >= warp_frame && do_warp(warp_area, warp_spawn)) warp_frame = -1;
    if (warp_pending >= 0) {
        if (do_warp(warp_pending >> 8, warp_pending & 0xFF)) { menu_open = 0; swallow = 0xFFFF; }
        else say("NOT IN GAMEPLAY");
        warp_pending = -1;
    }
    /* live cheats: memory only, in gameplay only (while an area loads, the player actor is being set up) */
    if (in_gameplay()) {
        if (inf_hp) { if (G_MAXHP < 1) G_MAXHP = 4; P_(0x16E, s16) = G_MAXHP; P_(0x170, s16) = G_MAXHP; }
        if (inf_ap) G_AP = 9999999;
    }
    if (speed == 2 && saved_realtime < 0) { saved_realtime = port_realtime; port_realtime = 0; }
    if (speed != 2 && saved_realtime >= 0) { port_realtime = saved_realtime; saved_realtime = -1; }
    if (speed == 1) port_sleep_us(1000000ull / (unsigned)port_hz);
    if (combo) {
        menu_open = !menu_open;
        swallow = now;
        port_printf("[debug] frame %d: menu %s\n", port_frame, menu_open ? "open" : "closed");
        *buttons = 0;
        return;
    }
    if (menu_open) {
        if (press & 0x1008 && !(now & 0x0C00)) { menu_open = 0; swallow = now; *buttons = 0; return; }
        if (press & 0x0010) cursor = wrap(cursor - 1, N_LINES);
        if (press & 0x0040) cursor = wrap(cursor + 1, N_LINES);
        if (press & 0x0080) adjust(cursor, (now & 0x0100) ? -10 : -1);
        if (press & 0x0020) adjust(cursor, (now & 0x0100) ? 10 : 1);
        if (press & 0x4000) activate(cursor);
        fly_move(0);
        *buttons = 0;
        return;
    }
    now &= ~swallow;
    fly_move(now);
    if (fly) now &= ~0x4CF0;   /* the d-pad, L1 / R1 and Cross belong to the flight */
    *buttons = now;
}

/* ---- overlay: the 5x7 font of Tombi-Decomp's debugmenu.c, drawn into the RGB frame ---- */
static const u8 font[64][7] = {   /* ASCII 32..95, bit 4 = left column */
    {0,0,0,0,0,0,0}, {4,4,4,4,4,0,4}, {10,10,0,0,0,0,0}, {10,31,10,10,31,10,0}, {4,15,20,14,5,30,4}, {24,25,2,4,8,19,3},
    {12,18,20,8,21,18,13}, {4,4,0,0,0,0,0}, {2,4,8,8,8,4,2}, {8,4,2,2,2,4,8}, {0,4,21,14,21,4,0}, {0,4,4,31,4,4,0},
    {0,0,0,0,12,4,8}, {0,0,0,31,0,0,0}, {0,0,0,0,0,12,12}, {0,1,2,4,8,16,0},
    {14,17,19,21,25,17,14}, {4,12,4,4,4,4,14}, {14,17,1,2,4,8,31}, {31,2,4,2,1,17,14}, {2,6,10,18,31,2,2},
    {31,16,30,1,1,17,14}, {6,8,16,30,17,17,14}, {31,1,2,4,8,8,8}, {14,17,17,14,17,17,14}, {14,17,17,15,1,2,12},
    {0,12,12,0,12,12,0}, {0,12,12,0,12,4,8}, {2,4,8,16,8,4,2}, {0,0,31,0,31,0,0}, {8,4,2,1,2,4,8}, {14,17,1,2,4,0,4},
    {14,17,23,21,23,16,14}, {14,17,17,17,31,17,17}, {30,17,17,30,17,17,30}, {14,17,16,16,16,17,14}, {28,18,17,17,17,18,28},
    {31,16,16,30,16,16,31}, {31,16,16,30,16,16,16}, {14,17,16,23,17,17,15}, {17,17,17,31,17,17,17}, {14,4,4,4,4,4,14},
    {7,2,2,2,2,18,12}, {17,18,20,24,20,18,17}, {16,16,16,16,16,16,31}, {17,27,21,21,17,17,17}, {17,17,25,21,19,17,17},
    {14,17,17,17,17,17,14}, {30,17,17,30,16,16,16}, {14,17,17,17,21,18,13}, {30,17,17,30,20,18,17}, {15,16,16,14,1,1,30},
    {31,4,4,4,4,4,4}, {17,17,17,17,17,17,14}, {17,17,17,17,17,10,4}, {17,17,17,21,21,21,10}, {17,17,10,4,10,17,17},
    {17,17,17,10,4,4,4}, {31,1,2,4,8,16,31}, {14,8,8,8,8,8,14}, {0,16,8,4,2,1,0}, {14,2,2,2,2,2,14}, {4,10,17,0,0,0,0},
    {0,0,0,0,0,0,31}};
static u8 *fb;
static int fb_w, fb_h, fb_sx;
static void fill(int x, int y, int w, int h, u32 rgb) {   /* x, y in 320-wide units */
    for (int j = y; j < y + h; j++) {
        if (j < 0 || j >= fb_h) continue;
        for (int i = x * fb_sx; i < (x + w) * fb_sx; i++) {
            if (i < 0 || i >= fb_w) continue;
            u8 *o = fb + (j * fb_w + i) * 3;
            o[0] = rgb >> 16; o[1] = rgb >> 8; o[2] = rgb;
        }
    }
}
static void shade(int x, int y, int w, int h) {   /* a darkened box */
    for (int j = y; j < y + h; j++) {
        if (j < 0 || j >= fb_h) continue;
        for (int i = x * fb_sx; i < (x + w) * fb_sx; i++) {
            if (i < 0 || i >= fb_w) continue;
            u8 *o = fb + (j * fb_w + i) * 3;
            o[0] >>= 2; o[1] >>= 2; o[2] >>= 2;
        }
    }
}
static void text(int x, int y, const char *s, u32 col) {
    for (; *s; s++, x += 6) {
        int c = *s;
        if (c >= 'a' && c <= 'z') c -= 32;
        if (c < 32 || c > 95) c = '?';
        for (int r = 0; r < 7; r++)
            for (int k = 0; k < 5; k++)
                if (font[c - 32][r] & (16 >> k)) { fill(x + k + 1, y + r + 1, 1, 1, 0); fill(x + k, y + r, 1, 1, col); }
    }
}
/* the displayed frame as RGB24 (shims/gpu.c, before the TV window shift: rows 0..223 are what a TV shows) */
void port_debug_draw(u8 *rgb, int w, int h) {
    char b[64];
    const u32 white = 0xFFFFFF, yellow = 0xFFFF40, green = 0x40FF40;
    fb = rgb; fb_w = w; fb_h = h; fb_sx = w >= 512 ? 2 : 1;
    if (overlay) {
        shade(2, 2, 216, 30);
        fmt(b, sizeof b, "F%d %d.%02dVB/S %s-%d%s", port_frame, fps_x100 / 100, fps_x100 % 100, area_name(G_AREA <= 0x15 ? G_AREA : 0),
            G_ARRIVAL, in_gameplay() ? "" : " (NO PLAY)");
        text(4, 4, b, green);
        fmt(b, sizeof b, "X%d Y%d Z%d HP%d/%d AP%d", P_(0x2E, s16), P_(0x32, s16), P_(0x36, s16), P_(0x16E, s16), G_MAXHP, G_AP);
        text(4, 13, b, green);
        if (port_debug_noclip || fly || inf_hp || inf_ap || speed) {
            fmt(b, sizeof b, "%s%s%s%s%s", port_debug_noclip ? "NOCLIP " : "", fly ? "FLY " : "", inf_hp ? "INFHP " : "",
                inf_ap ? "MAXAP " : "", speed == 1 ? "SLOW" : speed == 2 ? "FAST" : "");
            text(4, 22, b, yellow);
        }
    }
    if (msg_t > 0) text(4, 206, msg, yellow);
    if (menu_open) {
        int x0 = 24, y0 = 60, lh = 10;
        shade(x0 - 4, y0 - 14, 272, N_LINES * lh + 18);
        text(x0, y0 - 11, "DEBUG MENU  X=OK  TRI=CLOSE  L2=X10", white);
        for (int i = 0; i < N_LINES; i++) {
            line_text(i, b, sizeof b);
            text(x0 + 8, y0 + i * lh, b, i == cursor ? yellow : white);
            if (i == cursor) text(x0, y0 + i * lh, ">", yellow);
        }
    }
}

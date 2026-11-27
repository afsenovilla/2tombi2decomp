/* Audio output of the port, first part: the CD's XA ADPCM audio (the music in CD/BGM.XA, the voices in VOICE.XA and
 * DEMO.XA), which is most of what Tomba! 2 plays.  The libsnd / SPU sound effects are still silent (sound_stub.c).
 *
 * The virtual disc (cd_virtual.inc) hands every sector the head passes while the game streams XA (ReadS with the
 * CdlModeAP bit, the Setfilter file / channel) to port_xa_sector as the raw 2352-byte sector read from the disc
 * image (the extracted XA files lost their subheaders).  The decoder follows psx-spx ("CDROM XA Audio ADPCM"):
 * 18 sound groups of 128 bytes per sector, 4-bit units with a shift / filter header, two-tap filters
 * (0, 60/64, 115/64 - 52/64, 98/64 - 55/64), stereo units alternating left / right with their own history, 37800 or
 * 18900 Hz (18900 is stored twice).  The decoded audio is queued at 37800 Hz and resampled (linear) to 44100 Hz;
 * every vblank produces 44100 / hz stereo frames: to the --window viewer's audio pipe (fd 3, s16le stereo, the
 * protocol of runtime/window.c) and to --dump-audio PATH (a WAV file, its sizes written at exit).  The CD mix and
 * volume follow SpuSetCommonAttr (cd.mix, cd.volume) and CdlMute / CdlDemute.  The clock is the vblank: the disc
 * streams 150 sectors per second at double speed (2.5 per NTSC vblank), so the queue neither grows nor drains. */
#include "port_runtime.h"

typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32;

/* ----------------------------------------------------------------------------------------------- the XA queue */
#define QLEN 65536                          /* stereo frames at 37800 Hz (1.7 s) */
static s16 q[QLEN][2];
static unsigned q_r, q_w;                   /* positions; q_w - q_r = fill */
static int hist[2][2];                      /* ADPCM history per channel: [ch][0] = old, [ch][1] = older */
int port_xa_mute;                           /* CdlMute */
static int cd_mix = 1, cd_vol_l = 0x7FFF, cd_vol_r = 0x7FFF;
static unsigned long xa_sectors, xa_dropped;

static void q_put(int l, int r) {
    if (q_w - q_r >= QLEN) { q_r++; xa_dropped++; }
    q[q_w % QLEN][0] = (s16)l; q[q_w % QLEN][1] = (s16)r; q_w++;
}
static int clamp16(int v) { return v > 32767 ? 32767 : v < -32768 ? -32768 : v; }
static const int f0[4] = { 0, 60, 115, 98 }, f1[4] = { 0, 0, -52, -55 };

static void decode_unit(const u8 *grp, int unit, int bits8, s16 *out, int *h) {
    int head = grp[4 + unit], shift = head & 15, filt = (head >> 4) & 3;
    if (shift > 12) shift = 9;
    for (int j = 0; j < 28; j++) {
        int s;
        if (bits8) s = (s16)(grp[16 + j * 4 + unit] << 8);
        else { int b = grp[16 + j * 4 + unit / 2]; s = (s16)(((unit & 1) ? b >> 4 : b & 15) << 12); }
        s >>= shift;
        s += (h[0] * f0[filt] + h[1] * f1[filt] + 32) >> 6;
        s = clamp16(s);
        h[1] = h[0]; h[0] = s;
        out[j] = (s16)s;
    }
}

/* one raw 2352-byte sector (sync, header, subheader at 16, data at 24) */
void port_xa_sector(const u8 *raw) {
    const u8 *sh = raw + 16;
    if (!(sh[2] & 0x04)) return;            /* not an audio sector */
    int coding = sh[3], stereo = (coding & 3) == 1, half = (coding >> 2) & 1, bits8 = (coding >> 4) & 1;
    int units = bits8 ? 4 : 8;
    xa_sectors++;
    for (int g = 0; g < 18; g++) {
        const u8 *grp = raw + 24 + g * 128;
        s16 buf[8][28];
        for (int u = 0; u < units; u++) decode_unit(grp, u, bits8, buf[u], hist[stereo ? (u & 1) : 0]);
        if (stereo) {
            for (int u = 0; u < units; u += 2)
                for (int j = 0; j < 28; j++) {
                    q_put(buf[u][j], buf[u + 1][j]);
                    if (half) q_put(buf[u][j], buf[u + 1][j]);
                }
        } else {
            for (int u = 0; u < units; u++)
                for (int j = 0; j < 28; j++) {
                    q_put(buf[u][j], buf[u][j]);
                    if (half) q_put(buf[u][j], buf[u][j]);
                }
        }
    }
}
void port_xa_reset(void) { hist[0][0] = hist[0][1] = hist[1][0] = hist[1][1] = 0; }

/* ----------------------------------------------------------------------------------------------- libspu: the CD mix */
typedef struct { s16 left, right; } SpuVolume;
typedef struct { SpuVolume volume; int reverb; int mix; } SpuExtAttr;
typedef struct { u32 mask; SpuVolume mvol; SpuVolume mvolmode; SpuVolume mvolx; SpuExtAttr cd; SpuExtAttr ext; } SpuCommonAttr;
void SpuSetCommonAttr(SpuCommonAttr *a) {
    if (a->mask & 0x40) cd_vol_l = a->cd.volume.left;     /* SPU_COMMON_CDVOLL */
    if (a->mask & 0x80) cd_vol_r = a->cd.volume.right;    /* SPU_COMMON_CDVOLR */
    if (a->mask & 0x200) cd_mix = a->cd.mix;              /* SPU_COMMON_CDMIX */
}

/* ----------------------------------------------------------------------------------------------- output */
static int audio_fd = -1;                   /* --window: the viewer's audio pipe */
void port_pipe_audio_fd(int fd) { audio_fd = fd; }
const char *port_dump_audio;                /* --dump-audio PATH: a 44.1 kHz stereo WAV of everything played */
static int dump_fd = -1;
static unsigned long dump_bytes;
static unsigned frac;                       /* resampler position in 1/65536 source frames */
extern int port_hz, port_frame;
extern int port_write_all(int fd, const void *b, int n);

static void wav_header(u8 *h, u32 data) {
    static const u8 t[44] = { 'R','I','F','F',0,0,0,0,'W','A','V','E','f','m','t',' ',16,0,0,0,1,0,2,0,
                              0x44,0xAC,0,0,0x10,0xB1,2,0,4,0,16,0,'d','a','t','a',0,0,0,0 };
    for (int i = 0; i < 44; i++) h[i] = t[i];
    u32 riff = data + 36;
    h[4] = riff; h[5] = riff >> 8; h[6] = riff >> 16; h[7] = riff >> 24;
    h[40] = data; h[41] = data >> 8; h[42] = data >> 16; h[43] = data >> 24;
}
void port_audio_vblank(void) {
    if (audio_fd < 0 && !port_dump_audio) { q_r = q_w > q_r + 4096 ? q_w - 4096 : q_r; return; }
    int n = 44100 / (port_hz > 0 ? port_hz : 60);
    static s16 out[44100 / 50 + 8][2];
    const unsigned step = (unsigned)(37800ull * 65536 / 44100);
    int vl = cd_mix && !port_xa_mute ? cd_vol_l : 0, vr = cd_mix && !port_xa_mute ? cd_vol_r : 0;
    for (int i = 0; i < n; i++) {
        int l = 0, r = 0;
        if (q_w - q_r >= 2) {
            const s16 *a = q[q_r % QLEN], *b = q[(q_r + 1) % QLEN];
            int t = (int)(frac >> 4);       /* 0..4095 */
            l = a[0] + (((b[0] - a[0]) * t) >> 12);
            r = a[1] + (((b[1] - a[1]) * t) >> 12);
            frac += step;
            q_r += frac >> 16; frac &= 0xFFFF;
        }
        out[i][0] = (s16)clamp16((l * vl) >> 15);
        out[i][1] = (s16)clamp16((r * vr) >> 15);
    }
    if (audio_fd >= 0 && port_write_all(audio_fd, out, n * 4) != n * 4) audio_fd = -1;
    if (port_dump_audio) {
        if (dump_fd < 0) {
            dump_fd = port_create(port_dump_audio);
            if (dump_fd < 0) { port_printf("[port] cannot write %s\n", port_dump_audio); port_dump_audio = 0; return; }
            u8 h[44]; wav_header(h, 0x7FFFFFF0u); port_write(dump_fd, h, 44);
        }
        port_write(dump_fd, out, n * 4);
        dump_bytes += (unsigned long)n * 4;
    }
}
void port_audio_quit(void) {
    if (dump_fd >= 0) {
        u8 h[44]; wav_header(h, (u32)dump_bytes);
        port_pwrite(dump_fd, h, 44, 0);
        port_close(dump_fd); dump_fd = -1;
        port_printf("[port] audio: %lu XA sectors decoded, %lu frames dropped; %lu bytes in %s\n", xa_sectors, xa_dropped,
                    dump_bytes, port_dump_audio);
    }
}

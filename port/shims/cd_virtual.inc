/* ================================================================== libcd: a virtual disc (included by psyq.c)
 *
 * The player's disc is read as extracted files (game/usa/: the ISO9660 tree as the bootstrap extracts it; --data
 * DIR names another).  CdSearchFile opens the file and gives it a made-up position on a virtual disc: each file
 * gets its own range of 2048-byte sectors, so a Setloc anywhere inside a file (the game seeks into TOMBA2.DAT /
 * TOMBA2.IMG by sector offsets from TOMBA2.IDX) maps back to that file.  CdRead copies at once; the data-ready path
 * (CdControl ReadN / ReadS + CdReadyCallback + CdGetSector) delivers a few sectors per vblank. */
const char *port_data_dir = "game/usa";
int port_trace_cd;
int port_cd_open(const char *path) { (void)path; return -1; }
#define CD_FIRST_LBA 1000
typedef struct { char name[64]; int fd, lba, nsec; unsigned size; int img_lba; } CdFile;   /* img_lba: in --disc (-1: none) */
static CdFile cd_files[64];
static int n_cd_files, cd_next_lba = CD_FIRST_LBA;
static int cd_pos;                     /* next LBA */
static int cd_target, cd_target_pending; /* the last Setloc, not yet reached by a seek or a read */
static void *cd_ready_cb, *cd_sync_cb, *cd_read_cb, *cd_data_cb;
static u8 cd_mode = 0x80, cd_last_com;
static u8 cd_filter_file, cd_filter_chan;   /* Setfilter: the XA file / channel played */
static int cd_reading;                 /* ReadN / ReadS in progress: sectors are delivered on vblanks */
static u8 cd_sector[2352];
static u8 cd_result[8];
static int cd_sector_off;              /* CdGetSector read offset into cd_sector (bytes) */

static void cd_call(void *fn, u32 a, u32 b) {
    void (*f)(u32, u32) = (void (*)(u32, u32))fn;
    if ((u32)fn >= 0x80000000u && (u32)fn < 0x80200000u) f = (void (*)(u32, u32))port_resolve_call((u32)fn, "cd callback");
    f(a, b);
}
static int up(int c) { return c >= 'a' && c <= 'z' ? c - 32 : c; }
static void lba_to_loc(int lba, u8 *p);
/* The disc image (--disc, default game/usa.img: raw 2352-byte sectors), when there is one: XA audio needs the
   sectors' subheaders, which the extracted files lost (tools/isoext.py keeps only the user data).  A file's place
   on it comes from the ISO 9660 directory. */
const char *port_disc_image = "game/usa.img";
static int img_fd = -2;
static int img_open(void) {
    if (img_fd == -2) {
        img_fd = port_disc_image ? port_open(port_disc_image) : -1;
        if (img_fd >= 0) port_printf("[port] disc image %s (XA audio)\n", port_disc_image);
        else port_printf("[port] no disc image %s: XA music and voices are silent (--disc PATH)\n", port_disc_image ? port_disc_image : "-");
    }
    return img_fd;
}
static int img_read(int lba, u8 *raw) { return img_open() >= 0 && port_pread(img_fd, raw, 2352, (long long)lba * 2352) == 2352; }
static int iso_find(const char *rel, int *size) {      /* rel: "CD/BGM.XA" -> its first sector on the image, or -1 */
    static u8 sec[2352];
    if (!img_read(16, sec) || sec[25] != 'C' || sec[26] != 'D') return -1;
    const u8 *root = sec + 24 + 156;
    int lba = root[2] | root[3] << 8 | root[4] << 16 | root[5] << 24, len = root[10] | root[11] << 8 | root[12] << 16 | root[13] << 24;
    const char *p = rel;
    for (;;) {
        char comp[32]; int n = 0;
        while (*p && *p != '/' && n < 31) comp[n++] = *p++;
        comp[n] = 0;
        int found = 0;
        for (int k = 0; k < (len + 2047) / 2048 && !found; k++) {
            if (!img_read(lba + k, sec)) return -1;
            const u8 *d = sec + 24;
            for (int i = 0; i < 2048 && d[i];) {
                const u8 *e = d + i; int nl = e[32], m = 0;
                while (m < n && m < nl && e[33 + m] == comp[m]) m++;
                if (m == n && (nl == n || (nl > n && e[33 + n] == ';'))) {
                    lba = e[2] | e[3] << 8 | e[4] << 16 | e[5] << 24; len = e[10] | e[11] << 8 | e[12] << 16 | e[13] << 24;
                    found = 1; break;
                }
                i += e[0];
            }
        }
        if (!found) return -1;
        if (!*p) { *size = len; return lba; }
        p++;
    }
}
static CdFile *cd_find_lba(int lba) {
    for (int i = 0; i < n_cd_files; i++)
        if (lba >= cd_files[i].lba && lba < cd_files[i].lba + cd_files[i].nsec) return &cd_files[i];
    return 0;
}
int port_cd_read_sectors(int lba, int count, void *dst, int bytes) {
    u8 *d = dst;
    for (int i = 0; i < count; i++, d += bytes) {
        CdFile *f = cd_find_lba(lba + i);
        if (!f) { port_printf("[port] CD read of lba %d: no file there (frame %d)\n", lba + i, port_frame); return -1; }
        long long off = (long long)(lba + i - f->lba) * 2048;
        int skip = bytes > 2048 ? 12 : 0;    /* 2340-byte reads: the sector header (BCD position, mode 2) and the
                                                subheader (data, form 1), then the data (the game checks the position) */
        for (int k = 0; k < bytes; k++) d[k] = 0;
        if (skip) { lba_to_loc(lba + i, d); d[3] = 2; d[6] = d[10] = 0x08; }
        int got = port_pread(f->fd, d + skip, 2048, off);
        (void)got;
        if (port_trace_cd) port_printf("[port] cd: lba %d = %s sector %d\n", lba + i, f->name, lba + i - f->lba);
        if (lba + i == f->lba && f->name[0] == 'B' && f->name[1] == 'I' && f->name[2] == 'N' && f->name[3] == '/')
        {
            port_printf("[port] frame %d: loading %s\n", port_frame, f->name);   /* an overlay (or START.BIN) */
            port_ovl_loaded(f->name);   /* the native copy of its C is used from now on (sys_linux_i386.c) */
        }
    }
    return 0;
}
static int bcd(u8 b) { return (b >> 4) * 10 + (b & 15); }
static u8 tobcd(int v) { return (u8)((v / 10) << 4 | (v % 10)); }
static int loc_to_lba(const u8 *p) { return (bcd(p[0]) * 60 + bcd(p[1])) * 75 + bcd(p[2]) - 150; }
static void lba_to_loc(int lba, u8 *p) { lba += 150; p[0] = tobcd(lba / 4500); p[1] = tobcd(lba / 75 % 60); p[2] = tobcd(lba % 75); p[3] = 0; }

typedef struct { u8 pos[4]; u32 size; char name[16]; } CdlFILE;
CdlFILE *CdSearchFile(CdlFILE *fp, char *name) {
    char rel[64]; int n = 0;
    const char *s = name;
    while (*s == '\\' || *s == '/') s++;
    for (; *s && *s != ';' && n < 63; s++) rel[n++] = *s == '\\' ? '/' : (char)up(*s);
    rel[n] = 0;
    CdFile *f = 0;
    for (int i = 0; i < n_cd_files; i++) {
        int k = 0; while (rel[k] && rel[k] == cd_files[i].name[k]) k++;
        if (!rel[k] && !cd_files[i].name[k]) { f = &cd_files[i]; break; }
    }
    if (!f) {
        char path[512]; int o = 0;
        for (const char *d = port_data_dir; *d && o < 400; d++) path[o++] = *d;
        path[o++] = '/';
        for (int k = 0; rel[k] && o < 510; k++) path[o++] = rel[k];
        path[o] = 0;
        int fd = port_open(path);
        if (fd < 0 || n_cd_files == 64) {
            port_printf("[port] CdSearchFile(\"%s\"): %s not found (frame %d)\n", name, path, port_frame);
            return 0;
        }
        f = &cd_files[n_cd_files++];
        for (int k = 0; k <= n; k++) f->name[k] = rel[k];
        f->fd = fd;
        f->size = (unsigned)port_filesize(fd);
        f->nsec = (int)((f->size + 2047) / 2048);
        f->lba = cd_next_lba;
        cd_next_lba += f->nsec + 16;
        f->img_lba = -1;
        {   /* an XA file: its sectors on the image (the head position the game sees stays the virtual one) */
            int nm = 0; while (f->name[nm]) nm++;
            if (nm > 3 && f->name[nm - 3] == '.' && f->name[nm - 2] == 'X' && f->name[nm - 1] == 'A') {
                int isz = 0; f->img_lba = iso_find(f->name, &isz);
                if (f->img_lba >= 0) { f->nsec = (isz + 2047) / 2048; cd_next_lba = f->lba + f->nsec + 16; }
            }
        }
        port_printf("[port] CdSearchFile(\"%s\"): %s, %u bytes, virtual lba %d (frame %d)\n", name, path, f->size, f->lba, port_frame);
    }
    lba_to_loc(f->lba, fp->pos);
    fp->size = f->size;
    for (int k = 0; k < 16; k++) fp->name[k] = k < n ? rel[k] : 0;
    return fp;
}

int CdInit(void) { return 1; }
int CdReset(int m) { return 1; }
int CdStatus(void) { return 0x02; }
int CdMode(void) { return cd_mode; }
int CdLastCom(void) { return cd_last_com; }
int CdSetDebug(int l) { return 0; }
void CdFlush(void) {}
int CdControl(u8 com, u8 *param, u8 *result) {
    cd_last_com = com;
    /* Setloc only sets the target; SeekL / SeekP and the next ReadN / ReadS go there (the XA music player loops a
       track with SeekL + ReadS without parameters: the head must go back to the Setloc target) */
    if ((com == 2 /* Setloc */ || com == 0x15 || com == 0x16) && param) {
        cd_target = loc_to_lba(param); cd_target_pending = 1;
        if (port_trace_cd) port_printf("[port] cd: Setloc lba %d (frame %d)\n", cd_target, port_frame);
    }
    if (com == 0x15 /* SeekL */ || com == 0x16 /* SeekP */) { cd_pos = cd_target; cd_target_pending = 0; cd_reading = 0; }
    if ((com == 6 /* ReadN */ || com == 0x1B /* ReadS */)) {
        if (param) { cd_target = loc_to_lba(param); cd_target_pending = 1; }
        if (cd_target_pending) { cd_pos = cd_target; cd_target_pending = 0; }
        cd_reading = 1;
        if (port_trace_cd) port_printf("[port] cd: Read%s from lba %d (frame %d)\n", com == 6 ? "N" : "S", cd_pos, port_frame);
    }
    if (com == 9 /* Pause */ || com == 8 /* Stop */ || com == 0x0A /* Init */) cd_reading = 0;
    if (com == 14 /* Setmode */ && param) cd_mode = param[0];
    if (com == 0x0D /* Setfilter */ && param) { cd_filter_file = param[0]; cd_filter_chan = param[1]; }
    { extern int port_xa_mute; if (com == 0x0B) port_xa_mute = 1; else if (com == 0x0C) port_xa_mute = 0; }
    for (int i = 0; i < 8; i++) cd_result[i] = 0;
    cd_result[0] = cd_reading ? 0x22 : 0x02;
    if (com == 0x10) {          /* GetlocL: the header of the sector under the head (the XA player checks it) */
        lba_to_loc(cd_pos, cd_result); cd_result[3] = 2;
    } else if (com == 0x11) {   /* GetlocP: track 1, index 1, relative and absolute position */
        u8 loc[4];
        lba_to_loc(cd_pos, loc);
        cd_result[0] = 1; cd_result[1] = 1;
        lba_to_loc(cd_pos - 150 >= 0 ? cd_pos - 150 : 0, cd_result + 2);
        cd_result[5] = loc[0]; cd_result[6] = loc[1]; cd_result[7] = loc[2];
    }
    if (result) for (int i = 0; i < 8; i++) result[i] = cd_result[i];
    if (cd_sync_cb && com != 2) cd_call(cd_sync_cb, 2 /* CdlComplete */, (u32)result);
    return 1;
}
int CdControlF(u8 com, u8 *param) { return CdControl(com, param, 0); }
int CdControlB(u8 com, u8 *param, u8 *result) { return CdControl(com, param, result); }
/* CdSync hands back the last command's result bytes (GetlocL / GetlocP callers read them from here) */
int CdSync(int mode, u8 *result) { if (result) for (int i = 0; i < 8; i++) result[i] = cd_result[i]; return 2; /* CdlComplete */ }
int CdReady(int mode, u8 *result) { return cd_reading ? 1 : 2; }
void *CdSyncCallback(void *f) { void *o = cd_sync_cb; cd_sync_cb = f; return o; }
void *CdReadyCallback(void *f) { void *o = cd_ready_cb; cd_ready_cb = f; return o; }
void *CdReadCallback(void *f) { void *o = cd_read_cb; cd_read_cb = f; return o; }
void *CdDataCallback(void *f) { void *o = cd_data_cb; cd_data_cb = f; return o; }
int CdGetSector(void *buf, int words) {
    u8 *d = buf; int n = words * 4;
    for (int i = 0; i < n; i++) d[i] = cd_sector_off + i < (int)sizeof cd_sector ? cd_sector[cd_sector_off + i] : 0;
    cd_sector_off += n;
    return 1;
}
int CdGetSector2(void *buf, int words) { return CdGetSector(buf, words); }
int CdDataSync(int mode) { return 0; }
int CdRead(int sectors, u32 *buf, int mode) {
    int bytes = (mode & 0x20) ? 2340 : 2048;
    if (cd_target_pending) { cd_pos = cd_target; cd_target_pending = 0; }
    if (port_verbose || port_trace_cd) port_printf("[port] CdRead lba %d, %d sectors -> %p (frame %d)\n", cd_pos, sectors, buf, port_frame);
    if (port_cd_read_sectors(cd_pos, sectors, buf, bytes)) { port_printf("[port] CdRead failed at lba %d (frame %d)\n", cd_pos, port_frame); return 0; }
    cd_pos += sectors; cd_reads++; cd_sectors += sectors;
    if (cd_read_cb) cd_call(cd_read_cb, 2 /* CdlComplete */, 0);
    return 1;
}
int CdReadSync(int mode, u8 *result) { if (result) result[0] = 0x02; return 0; }
int CdReadBreak(void) { return 0; }
int CdMix(void *att) { return 1; }
int CdIntToPos(int i, u8 *p) { lba_to_loc(i, p); return (int)p; }
int CdPosToInt(u8 *p) { return loc_to_lba(p); }
int port_cd_stats(int *sectors) { *sectors = cd_sectors; return cd_reads; }
/* the data-ready path: up to 4 sectors per vblank (double speed is 150 sectors/s, 3 per PAL vblank) */
static void cd_vblank(void) {
    if (cd_reading && !cd_ready_cb) {
        /* XA audio streaming: the head moves 150 sectors/s at double speed (75 at single), 2.5 per NTSC vblank;
           the audio sectors of the Setfilter channel are played (shims/audio.c) */
        static int half;
        half += (cd_mode & 0x80) ? 300 / (port_hz > 0 ? port_hz : 60) : 150 / (port_hz > 0 ? port_hz : 60);
        int n = half / 2; half -= n * 2;
        for (int k = 0; k < n; k++, cd_pos++) {
            CdFile *f = cd_find_lba(cd_pos);
            if (!(cd_mode & 0x40) || !f || f->img_lba < 0) continue;
            static u8 raw[2352];
            if (!img_read(f->img_lba + cd_pos - f->lba, raw)) continue;
            if ((cd_mode & 0x08) && (raw[16] != cd_filter_file || raw[17] != cd_filter_chan)) continue;
            extern void port_xa_sector(const u8 *raw);
            port_xa_sector(raw);
        }
    }
    for (int k = 0; k < 4 && cd_reading && cd_ready_cb; k++) {
        int bytes = (cd_mode & 0x20) ? 2340 : 2048;
        if (port_cd_read_sectors(cd_pos, 1, cd_sector, bytes)) { cd_reading = 0; break; }
        cd_sector_off = 0;
        cd_pos++; cd_sectors++;
        static u8 res[8] = { 0x22 };
        cd_call(cd_ready_cb, 1 /* CdlDataReady */, (u32)res);
    }
}
/* streaming (movies): not supported yet; StGetNext reports no frame */
int CdRead2(int mode) { return 1; }
void StSetRing(void *a, int b) {}
void StClearRing(void) {}
void StUnSetRing(void) {}
int StFreeRing(void *a) { return 0; }
/* Movies are skipped (no MDEC yet; T1's trick): StGetNext hands the player a sector header whose frame number is past
   the end of every movie, so DEMO.BIN's player (func_801075F8: `frameCount >= limit` -> state 7) and the boot exe's
   take their own "movie finished" path at once. */
static struct { u16 id, type, secCount, nSectors; u32 frameCount, bsHeadSize; u16 width, height; } fake_st_header;
static u32 fake_st_frame[16];
int StGetNext(void **a, void **b) {
    fake_st_header.frameCount = 0x7FFFFFFF;
    fake_st_header.width = 320; fake_st_header.height = 240;
    *a = fake_st_frame; *b = &fake_st_header;
    if (port_verbose) port_printf("[port] movie skipped (StGetNext reports the last frame, frame %d)\n", port_frame);
    return 0;
}
void StSetStream(int a, int b, int c, void *d, void *e) {}
void StSetMask(int a, int b, int c) {}
/* MDEC (movies) */
void DecDCTReset(int m) {}
int DecDCTin(void *p, int m) { return 0; }
int DecDCTout(void *p, int n) { return 0; }
int DecDCTinSync(int m) { return 0; }
int DecDCToutSync(int m) { return 0; }
void *DecDCToutCallback(void *f) { return 0; }
void *DecDCTinCallback(void *f) { return 0; }
int DecDCTvlc(void *a, void *b) { return 0; }
int DecDCTvlcSize(int n) { return 0; }
int DecDCTBufSize(void *p) { return 0; }
